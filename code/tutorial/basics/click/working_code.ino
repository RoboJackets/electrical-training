#include <Wire.h>
#define DEVICE_ADDR 0x5A

void setup() {
    pinMode(10,OUTPUT);
    Wire.begin();
    writeRegister(0x01,0x00);
    writeRegister(0x02,0x00);
    writeRegister(0x0D,0x8E);
    writeRegister(0x0E,0x00);
    writeRegister(0x0F,0x00);
    writeRegister(0x10,0x00);
    writeRegister(0x13,0xFF);
    writeRegister(0x1A,0x36);
    writeRegister(0x1D,0xA0);

    writeRegister(0x01,0x00);
    writeRegister(0x03,0x02);
    writeRegister(0x04,0x54);
    writeRegister(0x05,0x01);
    writeRegister(0x06,0x00);
}

void loop() {
    writeRegister(0x0C,0x01);
    delay(2000);
}

void writeRegister(byte reg, byte val){
    Wire.beginTransmission(DEVICE_ADDR);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

void executeGo(){

}