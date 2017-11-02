#include "LCD.h"

LCD lcd;
int iterator = 0;

void setup() {
  lcd.writeTwoDigits(0, 1);
}

void loop() {
  if (iterator == 9)
    iterator = 0;
  else
    iterator++;

  lcd.writeDigit(iterator);
  delay(200);
}
