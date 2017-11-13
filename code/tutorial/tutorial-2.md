# Firmware Training Session 2
In this session, we'll learn how I2C protocol functions, develop a 
library for the Haptic Driver on the training board, and use it to interface
 with the Piezo buzzer onboard.

## I2C
A standard I2C is composed of 4 parts: **Start Condition, address frame, data fram and Stop Condition**

The following is an example that you can understand after reading the following 4 paragraphs:
![Sample I2C](images/i2c.png)

### Start Condition
To initiate a communication, the master device will leave SCL high (since SCL is constantly pulled high) and pull SDA low. This will notify all slave devices that a communication is going to happen. 
Just for fun fact if more than one master wish to transmit, whichever pulls SDA low first gains the control.

### Address Frame
After start condition is always the address frame. Usually address frame will have a 7-bit address (note that address is different from address frame), which points to what device and at what register (we'll talk about this later) we want to read/write to. Then it's followed by a R/W bit indicating this is either a read(1) or write(0) action. 
The 9th bit is the NACK/ACK bit. Once the first 8 bits were sent, slave device gain control over SDA line. If slave device did not pull this line low, it means that it either did not get the message or did not know how to interpret it. It is up to the master device to determine what happens next. This applies to both address frame and data frame. 

### Data Frame
Data will be transmitted after the address frame has completed transmission. Either slave/master will drive the SDA line depending on the R/W bit specified earlier in the address frame. There will also be a NACK/ACK bit appended to the end of transmitted data.

### Stop condition
The master will send a stop condition when data tranmission are complete. Stop condition is defined as a 0 to 1 change in SCL followed by 0 to 1 change in SDA. Be aware that this stop condition might be accidentally triggerred during data transmission so don't change SDA when SCL is pulled high.

## Piezo Buzzer
Piezo Buzzer are used for making beeps, tones and alerts, they look like this on your board.
![Piezo Buzzer](images/ps1240.jpg)

Piezo Buzzer utlises the effect called "Piezoelectric effect". In casual words it means: if you squeeze them, you can make electricity flow through them. The reverse also applies: if electricity flows through, they will squeeze themselves.
Which means, if you apply voltage and then let go of the voltage, it will essentially vibrates and create sound. 
We will use this property to make it generate sound.

## Haptic Driver
Haptic driver provides the necessary signal to make a piezo buzzer "buzz". They're the IC right next to piezo buzzer. 
