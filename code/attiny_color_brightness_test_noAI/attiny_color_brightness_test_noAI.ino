#include <SoftwareWire.h>

// SoftwareWire constructor.
// Parameters:
//   (1) pin for the software sda
//   (2) pin for the software scl
//   (3) use internal pullup resistors. Default true. Set to false to disable them.
//   (4) allow the Slave to stretch the clock pulse. Default true. Set to false for faster code.
//
// Using pin 2 (software sda) and 3 (software scl) in this example.

SoftwareWire myWire( 1, 0, 0);
int btn = 8;
int old_state;
int new_state;
void setup()
{
  pinMode(btn, INPUT);
  myWire.begin(); // join i2c bus (address optional for master)
  old_state = digitalRead(btn);


//  myWire.beginTransmission(byte(0x62)); // address
//  myWire.write(byte(0x11)); // subaddress + autoincrement
//  myWire.write(byte(0x00)); // prescalar PSC0 = 152 * (blink_period) - 1
//  myWire.write(byte(0x00)); // duty cycle PWM0 = (duty_cycle) * 256
//  myWire.write(byte(0x00)); // PSC1
//  myWire.write(byte(0x00)); // PWM1
//  myWire.write(byte(0x00)); // (LED3 | LED2 | LED1 | LED0)
//  myWire.endTransmission();     // stop transmitting
  led_off();

}


void loop()
{
  new_state = digitalRead(btn);
  if (old_state == 1 && new_state == 0){
    led_red();
    delay(500);
    led_blue();
    delay(500);
    led_green();
    delay(500);
  }
  led_off();
  old_state = new_state;
}

void led_off(){
  myWire.beginTransmission(byte(0x62)); // address
  myWire.write(byte(0x11)); // subaddress + autoincrement
  myWire.write(byte(0x00)); // prescalar PSC0 = 152 * (blink_period) - 1
  myWire.write(byte(0x00)); // duty cycle PWM0 = (duty_cycle) * 256
  myWire.write(byte(0x00)); // PSC1
  myWire.write(byte(0x00)); // PWM1
  myWire.write(byte(0x00)); // (LED3 | LED2 | LED1 | LED0)
  myWire.endTransmission();     // stop transmitting
}
void led_red(){
  //incomp
  myWire.beginTransmission(byte(0x62)); // address
  myWire.write(byte(0x05)); // subaddress + autoincrement
  myWire.write(byte(0x01)); // (LED3 | LED2 | LED1 | LED0)
  myWire.endTransmission();     // stop transmitting
}
void led_blue(){
  //incomp
   myWire.beginTransmission(byte(0x62)); // address
  myWire.write(byte(0x05)); // subaddress + autoincrement
  myWire.write(byte(0x4)); // (LED3 | LED2 | LED1 | LED0)
  myWire.endTransmission();     // stop transmitting
}
void led_green(){
  //incomp
  myWire.beginTransmission(byte(0x62)); // address
  myWire.write(byte(0x05)); // subaddress + autoincrement
  myWire.write(byte(0x10)); // (LED3 | LED2 | LED1 | LED0)
  myWire.endTransmission();     // stop transmitting
}
