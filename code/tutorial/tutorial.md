# Firmware Training Session #1
In this session, we will use the Arduino IDE for basic GPIO operations,
introduce pulse width modulation (PWM), and develop a firmware library for
interfacing with the shift registers and LCD on the training board.

## Setup
Install the Arduino IDE from 
[Arduino website](https://www.arduino.cc/en/Main/Software).

If you're running Windows, please install the USBtinyISP drivers from
Adafruit's website [here](https://learn.adafruit.com/usbtinyisp/drivers). These
drivers enable use of the Tiny AVR Programmer, which permits you to program your
board.

Our board uses a custom configuration, which is different from the standard
Arduino layout. We will therefore need to configure individual settings for
programming the ATMega328 chip. To do so, we will load in the MiniCore package:
1. Open the Arduino IDE

2. Go to **File > Preference**. Paste 
```text
https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json
``` 
into **Additional Boards Manager URLs** and press **OK**

3. Go to **Tools > Board > Boards Manager** and search for and install 


## Basics

### Blinky
### PWM

## LCD Buzzer

### Header file
### Source file
### Arduino script
