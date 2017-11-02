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
  // If both buttons pressed, blink the LED
  if (digitalRead(btn2) && digitalRead(btn3))
    ledState = !ledState;
  // If either button is pressed, turn LED on
  else if (digitalRead(btn2) || digitalRead(btn3))
    ledState = 1;
  // Otherwise, turn LED off
  else
    ledState = 0;

  digitalWrite(led, ledState);
  delay(50);
}
