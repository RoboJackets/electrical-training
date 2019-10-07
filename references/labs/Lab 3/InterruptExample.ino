#define STATE_A ? //define your state variables here
#define ...

const byte interruptPin1 = ?; //Assign pin numbers accordingly
const byte interruptPIn2 = ?; //the const keyword ensures the value does not change

volatile int state = 0; //the volatile keyword makes your code more reliable when using interrupts


void setup(){
    //define variables and do whatever you want here


    attachInterrupt(digitalPinToInterrupt(/* PIN NUMBER */), myISR, /* Trigger Condition */); //Triggers myISR on first input
    attachInterrupt(digitalPinToInterrupt(/* PIN NUMBER */), myISR, /* Trigger Condition */); //Triggers myISR on second input

}

void loop(){
    /*
       State machine code goes here
    */
}

void myISR() {

    //Include logic for state transitions here

}
