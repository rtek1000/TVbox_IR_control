// Remote control decoder (used in generic TV-box) - NEC type code
// by Rtek1000
// Mar/12/2024
//
// Ref.: https://www.sbprojects.net/knowledge/ir/nec.php

#if defined(ESP32)
const int IR_input_pin = 15;  // All
// Tested with ESP32 DEVKIT V1
#elif defined(ESP8266)
const int IR_input_pin = D5;
// Interrupts can be attached to any GPIO pin, except the D0/GPIO16 pin
// GPIO0 (D3) have pull-up (not good for IR)
// GPIO2 (D4) have pull-up (not good for IR)
// GPIO15 (D8) have pull-down (not good for IR)
// GPIO16 (D0) have pull-up LED_BUILTIN, and Interrupts can not be attached (not good for IR)
// Tested with Lolin New NodeMCU V3
// Ref.: https://i.pinimg.com/originals/f7/81/ef/f781efedf44a3b9673f1e88d2d8253c8.png
#else
const int IR_input_pin = 2;  // For ATmega328 (UNO/Nano/Pro Mini): 2, 3
// Tested with Arduino NANO (UNO bootloader)
#endif

// Change this setting to 1 to debug:
#define PRINT_TIMES 1

volatile bool nec_ok = false;
volatile bool nec_valid = false;
volatile uint8_t bit_n = 0;
volatile uint32_t timer_value1 = 0;
volatile uint32_t timer_value2 = 0;

#if PRINT_TIMES == 1
volatile uint32_t timer_value3 = 0;
#endif

volatile uint32_t nec_code = 0;
volatile uint16_t nec_code_repeat_old = 0;

volatile bool NEC_start = false;

#define repeat_ref1 2041
#define repeat_ref2 2541

#define logic_H_ref1 1500
#define logic_H_ref2 2000

#define logic_L_ref1 250
#define logic_L_ref2 750

struct NEC_code_t {
  volatile bool valid = false;
  volatile uint8_t address = 0;
  volatile uint8_t command = 0;
  volatile uint8_t repeat = 0;
};

enum TVbox_ctrl_code {
  _Power_ = 0x40,
  _Setup_ = 0x43,
  _APP_ = 0x0F,
  _VOL_DN_ = 0x10,
  _VOL_UP_ = 0x18,
  _Home_ = 0x11,
  _Return_ = 0x19,
  _Menu_ = 0x4C,
  _Mouse_ = 0x00,
  _Mute_ = 0x41,
  _BS_ = 0x42,
  _UP_ = 0x16,
  _DN_ = 0x1A,
  _L_ = 0x51,
  _R_ = 0x50,
  _OK_ = 0x13,
  _Unknown_ = 0xFF
};

const uint8_t TVbox_ctrl_addr = 0x01;
const char key1_char[][8] = { "Power", "Setup", "APP", "VOL DN",
                              "VOL UP", "Home", "Return", "Menu",
                              "Mouse", "Mute", "BS", "UP",
                              "Down", "Left", "Right", "OK",
                              "Unknown" };

const uint8_t key1_ref[17] = { _Power_, _Setup_, _APP_, _VOL_DN_,
                               _VOL_UP_, _Home_, _Return_, _Menu_,
                               _Mouse_, _Mute_, _BS_, _UP_,
                               _DN_, _L_, _R_, _OK_,
                               _Unknown_ };

const uint8_t Unknown_index = sizeof(key1_ref) - 1;

NEC_code_t NEC_code1;

const char start_txt[] = { "\n\nTV-box remote control decoder - NEC type - Start!" };
const char text1[] = { " - [NEC decode] - Addr: 0x" };
const char text2[] = { " Cmd: 0x" };
const char text3[] = { " Repeat: " };

#if defined(ESP32)
void IRAM_ATTR int_ISR() {
#elif defined(ESP8266)
void IRAM_ATTR int_ISR() {
#else
void int_ISR() {
#endif

  if (digitalRead(IR_input_pin) == HIGH) {
    timer_value1 = micros();
  } else {
    timer_value2 = micros() - timer_value1;

#if PRINT_TIMES == 1
    timer_value3 = timer_value2;
#endif

    if (NEC_start == false) {
      if ((timer_value2 > 4250) && (timer_value2 < 4750)) {  // 4.5ms (Part of header)
        NEC_start = true;
        nec_code = 0;
        bit_n = 0;

        NEC_code1.valid = false;
        NEC_code1.address = 0;
        NEC_code1.command = 0;
        NEC_code1.repeat = 0;
        nec_valid = false;
      } else if ((timer_value2 > repeat_ref1) && (timer_value2 < repeat_ref2)) {  // Repeat
        if (nec_valid == true) {
          NEC_code1.repeat++;
        }
      }
    } else {
      if ((timer_value2 > logic_H_ref1) && (timer_value2 < logic_H_ref2)) {  // Logic 1 (part of bit High)
        nec_code |= ((uint32_t)1 << bit_n);                                  // The LSB is sent first, then the MSB
        bit_n++;
      } else if ((timer_value2 > logic_L_ref1) && (timer_value2 < logic_L_ref2)) {  // Logic 0 (part of bit Low)
        bit_n++;
      }

      if (bit_n > 31) {
        uint8_t addr1 = (nec_code)&0xFF;
        uint8_t addr2 = ~(nec_code >> 8) & 0xFF;
        uint8_t cmd1 = (nec_code >> 16) & 0xFF;
        uint8_t cmd2 = ~((nec_code >> 24) & 0xFF);

        NEC_start = false;

        if ((addr1 != 0) && (addr1 == addr2) && (cmd1 == cmd1)) {
          nec_valid = true;
          NEC_code1.valid = true;
          NEC_code1.address = addr1;
          NEC_code1.command = cmd1;

          detachInterrupt(IR_input_pin);
        }
      }
    }
  }
} /* void IRAM_ATTR int_ISR() */

void setup() {
  delay(1000);

  Serial.begin(115200);

  Serial.println(start_txt);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(IR_input_pin, INPUT);

#if defined(ESP32)
  attachInterrupt(IR_input_pin, int_ISR, CHANGE);
#elif defined(ESP8266)
  attachInterrupt(digitalPinToInterrupt(IR_input_pin), int_ISR, CHANGE);
#else
  attachInterrupt(digitalPinToInterrupt(IR_input_pin), int_ISR, CHANGE);
#endif


} /* void setup() */

void loop() {
// Change this setting to 1 to debug: #define PRINT_TIMES 0
#if PRINT_TIMES == 1
  if (timer_value3 > 0) {
    Serial.println(timer_value3, DEC);

    timer_value3 = 0;
  }
#endif

  if (NEC_code1.valid == true) {
    NEC_code1.valid = false;

    print_text();

    attachInterrupt(IR_input_pin, int_ISR, CHANGE);
  } else if ((nec_code_repeat_old != NEC_code1.repeat) && (NEC_code1.repeat > 0)) {
    nec_code_repeat_old = NEC_code1.repeat;

    print_text();
  }
} /* void loop() */

void print_text() {
  Serial.print(TVbox_scan_code(NEC_code1));

  Serial.print(text1);
  Serial.print(NEC_code1.address, HEX);
  Serial.print(text2);
  Serial.print(NEC_code1.command, HEX);
  Serial.print(text3);
  Serial.println(NEC_code1.repeat, DEC);
}

const char* TVbox_scan_code(NEC_code_t Ncode) {
  if (Ncode.command != _Unknown_) {
    for (uint8_t i = 0; i < sizeof(key1_ref); i++) {
      if (Ncode.command == key1_ref[i]) {
        return key1_char[i];
      }
    }
  }

  return key1_char[Unknown_index];  // "Unknown"
} /* const char* TVbox_scan_code(NEC_code_t Ncode) */
