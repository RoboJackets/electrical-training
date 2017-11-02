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
`https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json` 
into **Additional Boards Manager URLs** and press **OK**
3. Go to **Tools > Board > Boards Manager** and search for and install 
`MiniCore`
4. Go to **Tools > Programmer** and select *USBtinyISP* as your programmer
5. Go to **Tools** and set the following settings:

| Parameter | Value |
|---|---|
| Board | *(MiniCore)* ATmega328 |
| Variant | 328p/ 328pa |
| BOD | 2.7V |
| Clock | 1 MHz Internal |
| Compiler LTO | Disabled |

Congratulations, we're now ready to get started!

## Basics
We will now explore different methods of interfacing with the ATmega328
microcontroller throught the Arduino IDE.

Generally, Arduino programs consist of a `setup()` functions, which run once,
and a `loop()` funciton, which continuously repeats.

### Blinky
In this section, we construct a program to interface with the onboard buttons
and LED. 

Begin a new sketch by opening the Arduino IDE and clicking **File > New**

A new window will appear with the following skeleton code:
```C
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```

We begin by setting the proper pin inputs into the MCU. We assign variables
`btn2`, `btn3`, and `led` to their corresponding connections, as can be
determined from the Eagle schematic. 

The buttons are connected pulled down, with an active high input into the MCU:
![buttons](images/buttons_pinout.PNG)

Likewise, the LED is connected to the MCU in a typical fashion:
![led](images/led_pinout.PNG)

These connections are then found on the actual ATmega schematic:
![atmega nobuttons](images/atmega_basics_pinout.PNG)

In order to retrieve the pin names as used in Arduino, we reference an ATmega328
pinout: ![atmega328](atmega328.png)

Cross-referencing our schematic with the pinout diagram, we find that our pins
have the following Arduino labels:

| Pin | Arduino Label |
| --- | --- |
| btn2 | A0 |
| btn3 | A1 |
| led | 10 |

Therefore, we insert constant definitions for the three pins in above 
`void setup() ...`:

```C
// Pin definitions
const int btn2 = A0;
const int btn3 = A1;
const int led  = 10;
```

In this program, we will read the values of both buttons. When no buttons are
pressed, the LED will be off. When one is pressed, the LED will be on. When both
buttons are pressed, the LED will flicker at a fast rate.

In order to be able to toggle the LED and to maintain cleaner code, we will have
an `ledState` variable that will keep track of whether the LED is on or off. By
setting this variable, we will be able to activate and deactivate the LED as
desired on every loop.

We thus declare and initialize an LED integer below the pin definitions:
```C
// Keep track of whether the LED is on or off at the present moment
int ledState = 0;
```

Next, we configure each of the pins as an input or output using Arduino's
`pinMode(..)` function. Each of these three statements goes in the setup()
function, which sets the direction of each of the pins:

```C
void setup() {
  // Set inputs and outputs
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(led, OUTPUT);
}
```
We're now ready to implement the actual program logic. This code goes in the
`void loop()` event loop, where it will read the inputs and update the outputs
in each cycle. We use the `digitalRead(..)` functions to read the values from
the digtial inputs, and based on these readings update the `ledState`.

Insert the following conditional logic into `loop()`:

```C
// If either button is pressed, turn LED on
if (digitalRead(btn2) || digitalRead(btn3))
  ledState = 1;
// If both buttons pressed, blink the LED
else if (digitalRead(btn2) && digitalRead(btn3))
  ledState = !ledState;
// Otherwise, turn LED off
else
  ledState = 0;
```

We then write the `ledState` to the LED pin and use the `delay(..)` function to
stall the program for 50 milliseconds:

```C
digitalWrite(led, ledState);
delay(50);
```

Ultimately, the program will look as follows:

```C
// Pin definitions
const int btn2 = A0;
const int btn3 = A1;
const int led  = 10;

// Keep track of whether the LED is on or off at the present moment
int ledState = 0;

void setup() {
  // Set inputs and outputs
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // If either button is pressed, turn LED on
  if (digitalRead(btn2) || digitalRead(btn3))
    ledState = 1;
  // If both buttons pressed, blink the LED
  else if (digitalRead(btn2) && digitalRead(btn3))
    ledState = !ledState;
  // Otherwise, turn LED off
  else
    ledState = 0;

  digitalWrite(led, ledState);
  delay(50);
}
```

Upload to the Arduino by clicking on **Sketch > Upload Using Programmer**, and
observe how pressing the buttons changes the LED output.

### PWM
We will now use pulse width modulation to control the brightness of the LED. PWM
works by outputting a square wave at a set frequency, while varying its duty
cycle (the ratio of the time the wave is HIGH to the total period of the
waveform). An example of PWM waveforms at different duty cycles is shown below:
![pwm](images/pwm.png)

Arduino supports a PWM resolution of 256 bits. To output a PWM signal from a
pin, begin by setting the pin to output with `pinMode( <PIN_NAME>, OUTPUT )`
and use the `analogWrite(..)` function:
`analogWrite( <PIN_NAME>, <VALUE_BETWEEN_0_AND_255> )`

We show this by creating a new Arduino project called *pwm*, where we use button
*btn2* and the LED to toggle the LED between being off and on at brightness
specified by the PWM duty cycle. The LED output will toggle on each button
press.

First, we define the button and LED pins above `void setup()`:
```C
// Pin definitions
const int btn2 = A0;
const int led  = 10;
```

We will keep track of whether the LED is toggled on or off by using the 
`pwmState` variable:

```C
// Keep track of whether PWM is enabled or disabled
int pwmState = 0;
```

In order to determine when the button is pressed, we will monitor the state of
the button on every clock cyle. 

```C
// Keep track of the current and previous state of the button
int buttonState, buttonStateOld;
```

Finally, we set a constant duty cycle we wish to output to the PWM:

```C
// Duty cycle to write to the LED
const int dutyCycle = 200;
```

We now enter the `setup()` function, where we set the button to an input and the
LED to an output.

```C
void setup() {
  // Set inputs and outputs
  pinMode(btn2, INPUT);
  pinMode(led, OUTPUT);
```
We also initialize the old button state by doing a preliminary reading of the
pushbutton:

```C
  // Initialize the old reading of the button before entering main loop
  buttonStateOld = digitalRead(btn2);
}
```

We are now ready to enter the event loop. We begin by reading the current state
of the button:

```C
void loop() {
  // Read the new button input
  buttonState = digitalRead(btn2);
```

We then check if the button is different from its previous state. If so, we
toggle the `pwmState` variable:

```C
  // If a change is detected in the button, then toggle the PWM state
  if (!buttonStateOld && buttonState)
    pwmState = !pwmState;
```

We then update the old button state, so that the loop can compare with the
current button value:

```C
  // Update the old button state
  buttonStateOld = buttonState;
```

Finally, depending on whether `pwmState` is toggled or not, we write either
`dutyCycle` or `0` to the PWM:

```C

  // Depending on PWM state, output either a PWM at the duty cycle or 0
  if (pwmState)
    analogWrite(led, dutyCycle);
  else
    analogWrite(led, 0);
  
  delay(20);
}
```

Your button should now toggle every time it is presses. Experiment with changing
the button brightness by changing the `dutyCycle` value.





## LCD Buzzer

### Header file
### Source file
### Arduino script
