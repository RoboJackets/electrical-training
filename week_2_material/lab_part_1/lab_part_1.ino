int forward_high = 3;
int backward_high = 5;
int forward_low = 2;
int backward_low = 9;

int direction_switch = 4;
int enable_switch = 13;

void apply_forward(){
  digitalWrite(forward_high, LOW);
  digitalWrite(forward_low, HIGH);
  digitalWrite(backward_high, HIGH);
  digitalWrite(backward_low, LOW);
  
}

void apply_backward(){
  digitalWrite(forward_high, HIGH);
  digitalWrite(forward_low, LOW);
  digitalWrite(backward_high, LOW);
  digitalWrite(backward_low, HIGH);
  
}

void apply_stop(){
  digitalWrite(forward_high, HIGH);
  digitalWrite(forward_low, LOW);
  digitalWrite(backward_high, HIGH);
  digitalWrite(backward_low, LOW);
}

void setup() {
  // put your setup code here, to run once:

  pinMode(forward_high, OUTPUT);
  pinMode(backward_high, OUTPUT);
  pinMode(forward_low, OUTPUT);
  pinMode(backward_low, OUTPUT);

  pinMode(direction_switch, INPUT);
  pinMode(enable_switch, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(enable_switch)){
    if(digitalRead(direction_switch)){
      apply_forward();
    }
    else{
      apply_backward();
    }
  }
  else{
    apply_stop();
  }
}
