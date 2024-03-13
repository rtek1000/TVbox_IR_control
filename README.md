# TVbox IR control
A NEC protocol based IR remote control

-----

Note: TV Control buttons are not supported in this code (Unless controls with NEC protocol are cloned)
- - (Pwr, Set, TV IN, VOL+, VOL-)
- - The "TV control" buttons must be programmed by the user, to clone the signal from the original TV control.
- - Procedures for performing control programming are [below](https://github.com/rtek1000/TVbox_IR_control/blob/main/README.md#procedures-for-programming-the-tv-control-buttons).
 
![img](https://github.com/rtek1000/TVbox_IR_control/blob/main/TVbox_IR_control_TV_Control.jpg)

- That's why the "TV Control" buttons on the TV-Box control come from the factory with the code 0xFF in the NEC protocol.
 
![img](https://raw.githubusercontent.com/rtek1000/TVbox_IR_control/main/TV_Control_Pwr_Pulse_train.png)

-----

- Boards: Arduino (UNO, NANO, Pro Mini), ESP8266, ESP32
- - The code can be adapted to other boards, it only needs external interrupt and micros().

Arduino NANO:
> Sketch uses 3496 bytes (10%) of program storage space. Maximum is 32256 bytes.
> 
> Global variables use 468 bytes (22%) of dynamic memory, leaving 1580 bytes for local variables. Maximum is 2048 bytes.

-----

TVbox IR remote control:
- Uses 2 AAA type batteries

![TVbox_IR_ctrl](https://raw.githubusercontent.com/rtek1000/TVbox_IR_control/main/TVbox_IR_control1.jpg)

NEC protocol:
- This code only monitors the time of the intervals (space):

![NEC_Protocol](https://raw.githubusercontent.com/rtek1000/TVbox_IR_control/main/NEC-Protocol-Transmission.png)

-----

I found an IR remote control graphic analyzer, available on this [website](https://www.circuitlake.com/ir-protocol-analyzer-software.html), for use on a PC with a receiver adapted for microphone input, it could be a good tool to see exactly what the signal is like.(But if you have the "Saleae" type logic analyzer or another, it should be better than this via the PC sound card)

![img](https://lh5.googleusercontent.com/-Quaeze3-1Mk/Toewz1Y24FI/AAAAAAAAAZo/NYKudqMrQ3o/IR%252520protocol%252520analyzer.jpg)

-----

## Procedures for programming the TV Control buttons

![img](https://raw.githubusercontent.com/rtek1000/TVbox_IR_control/main/TVbox_IR_control_TV_Control.jpg)

1 - Press the "TV Control - Power" button on the TV-box control (right side) until the button lights up without flashing, then release the button. (About 5 seconds, if it doesn't work, try changing the batteries. Or the control is a "copy" without the ability to clone other controls)

2 - Press and release the button on the TV-box control (only the "TV Control" buttons) that you want to program, the "TV Control - Power" button on the TV-box control should be flashing.

3 - Position the original TV control in front of the TV-Box control and press the desired key on the original TV control.
The two controls must have the emitters aligned facing each other.
The "TV Control - Power" button on the TV-Box control should flash 3 times to indicate that it has recognized the signal from the original TV control.

4- Press the "TV Control - Power" button on the TV-Box once more, and the "TV Control - Power" button on the TV-Box should start flashing again. Then press the same button on the original TV control 1 more time. The TV-Box's "TV Control - Power" button should stop flashing and remain off.

5- Test the "TV Control - Power" button on the TV-Box to control the TV. If it didn't work, try programming again, starting from step 1.

Reference video: [[How To: Program The LeelBox Q1 Smart TV Box Remote](https://www.youtube.com/watch?app=desktop&v=lUNzTHOpiY8)] 

-----

Licence:

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
