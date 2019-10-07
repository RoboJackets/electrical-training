#define STATE_A 0 //state definitions
#define ...

int state = 0; //state variable

void setup() {
    //set pin modes and begin any required communications
    
}

void loop() {

    switch (state) {
        case /* First State */:
            firstStateCode(); //call function which does all the things you would want to do in state 1
            if(/* Transition Condition */) {
                state = /* New State */;
            }
            break;
        case /* Second State */:
            secondStateCode();
            break;
        case ...

        default:
            break;


}

void firstStateCode() { //there are better names than this...
    //write all functionality that would happen during the state in here
}
