// Pin definitions
const int btn2 = A0;
const int led  = 10;

// Keep track of whether PWM is enabled or disabled
int pwmState = 0;

// Keep track of the current and previous state of the button
int buttonState, buttonStateOld;

// Duty cycle to write to the LED
const int dutyCycle = 200;

void setup() {
  // Set inputs and outputs
  pinMode(btn2, INPUT);
  pinMode(led, OUTPUT);
  
  // Initialize the old reading of the button before entering main loop
  buttonStateOld = digitalRead(btn2);
}

void loop() {
  // Read the new button input
  buttonState = digitalRead(btn2);

  // If a change is detected in the button, then toggle the PWM state
  if (!buttonStateOld && buttonState)
    pwmState = !pwmState;

  // Update the old button state
  buttonStateOld = buttonState;

  // Depending on PWM state, output either a PWM at the duty cycle or 0
  if (pwmState)
    analogWrite(led, dutyCycle);
  else
    analogWrite(led, 0);
}
