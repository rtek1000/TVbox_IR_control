# TVbox IR control
A NEC protocol based IR remote control
- Note: TV Control buttons are not supported in this code
- - (Pwr, Set, TV IN, VOL+, VOL-)

- Boards: Arduino (UNO, NANO, Pro Mini), ESP8266, ESP32
- - The code can be adapted to other boards, it only needs external interrupt and micros().

Arduino NANO:
> Sketch uses 3496 bytes (10%) of program storage space. Maximum is 32256 bytes.
> 
> Global variables use 468 bytes (22%) of dynamic memory, leaving 1580 bytes for local variables. Maximum is 2048 bytes.

TVbox IR remote control:
- Uses 2 AAA type batteries

![TVbox_IR_ctrl](https://raw.githubusercontent.com/rtek1000/TVbox_IR_control/main/TVbox_IR_control1.jpg)

NEC protocol:
- This code only monitors the time of the intervals (space):

![NEC_Protocol](https://raw.githubusercontent.com/rtek1000/TVbox_IR_control/main/NEC-Protocol-Transmission.png)

-----

I found an IR remote control graphic analyzer, available on this [website](https://www.circuitlake.com/ir-protocol-analyzer-software.html), for use on a PC with a receiver adapted for microphone input, it could be a good tool to see exactly what the signal is like.

![img](https://lh5.googleusercontent.com/-Quaeze3-1Mk/Toewz1Y24FI/AAAAAAAAAZo/NYKudqMrQ3o/IR%252520protocol%252520analyzer.jpg)

-----

Licence:

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
