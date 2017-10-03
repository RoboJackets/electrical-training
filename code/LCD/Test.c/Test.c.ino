#include <avr/io.h>
//int latchPin = PD2;
//int clockPin = PD1;
//int dataPin = PD0;


int main(){
//  pinMode(latchPin,OUTPUT);
//  pinMode(clockPin,OUTPUT);
//  pinMode(dataPin,OUTPUT);
  pinMode(0x03,OUTPUT);

   while(1){
    digitalWrite(0x03,HIGH);
    delay(300);
    digitalWrite(0x03,LOW);
    delay(300);
  }
}

