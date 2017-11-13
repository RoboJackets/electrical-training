#include <Arduino.h>

#include "lcd.h"

LCD::LCD()
{
    com = A2;
    oe_n = 5;
    latch = 6;
    clk = 7;
    reset_n = 8;
    data = 9;

    pinMode(com, OUTPUT);
    pinMode(oe_n, OUTPUT);
    pinMode(latch, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(reset_n, OUTPUT);
    pinMode(data, OUTPUT);

    digitalWrite(com, LOW);

    digitalWrite(latch, LOW);
    digitalWrite(oe_n, LOW);
}

LCD::LCD(int com_i, int oe_n_i, int latch_i, int clk_i, 
        int reset_n_i, int data_i)
{
    com = com_i;
    oe_n = oe_n_i;
    latch = latch_i;
    clk = clk_i;
    reset_n = reset_n_i;
    data = data_i;

    pinMode(com, OUTPUT);
    pinMode(oe_n, OUTPUT);
    pinMode(latch, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(reset_n, OUTPUT);
    pinMode(data, OUTPUT);

    digitalWrite(com, LOW);

    digitalWrite(latch, LOW);
    digitalWrite(oe_n, LOW);
}

// Tick the clock a single time
void LCD::clkTick()
{
    digitalWrite(clk, LOW);
    delay(DELAY_HALF_PERIOD);
    digitalWrite(clk, HIGH);
    delay(DELAY_HALF_PERIOD);
    digitalWrite(clk, LOW);
}

// Tick the latch a single time
void LCD::latchTick()
{
    digitalWrite(latch, LOW);
    delay(DELAY_HALF_PERIOD);
    digitalWrite(latch, HIGH);
    delay(DELAY_HALF_PERIOD);
    digitalWrite(latch, LOW);
}

// Convert digit into bitwise encoding
int LCD::getBits(int digit)
{
    /*
     * We encode digits in 
     *     [ A | B | C | D | E | F | G | DP/Col ] 
     * format
     */
    switch (digit) {
        case 0:
            return 0xFC;
        case 1:
            return 0x60;
        case 2:
            return 0xDA;
        case 3:
            return 0xF2;
        case 4:
            return 0x66;
        case 5:
            return 0xB6;
        case 6:
            return 0xBE;
        case 7:
            return 0xE0;
        case 8:
            return 0xFE;
        case 9:
            return 0xF6;
        default:
            return 0x00;
    }
}

void LCD::clear()
{
    digitalWrite(reset_n, LOW);
    clkTick();        
    digitalWrite(reset_n, HIGH);

    latchTick();
}

void LCD::sendDigit(int digit)
{
    digitalWrite(latch, LOW);

    int digitBits = getBits(digit);

    digitalWrite(reset_n, HIGH);

    for (int i=0; i<BITS_PER_DIGIT; ++i) {
        digitalWrite(data, digitBits & 0x1);
        clkTick();
        digitBits >>= 1;
    }
}

void LCD::writeDigit(int digit)
{
    clear();
    sendDigit(digit);
    
    latchTick();
}

void LCD::writeTwoDigits(int digit1, int digit2)
{
    clear();
    sendDigit(digit1);
    sendDigit(digit2);
    
    latchTick();
}
