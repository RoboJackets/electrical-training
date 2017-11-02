#include "Arduino.h"

#include "lcd.h"

LCD::LCD()
{
    com = com_i;
    oe_n = oe_n_i;
    latch = latch_i;
    clk = clk_i;
    reset_n = reset_n_i;
    data = data_i;
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

    digitalWrite(oe_n, LOW);
}

// Tick the clock a single time
void LCD::clkTick()
{
    digitalWrite(clk, LOW);
    delay(DELAY_HALF_PERIOD);
    digitalWrite(clk, HIGH);
    delay(DELAY_HALF_PERIOD);
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
            return 0xFA;
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
            return 0xE6;
        case 9:
            return 0xFA;
        default:
            return 0x00;
    }



void LCD::clear()
{
    digitalWrite(com, HIGH);
    digitalWrite(reset, LOW);
    clkTick();        
    digitalWrite(com, LOW);
    digitalWrite(reset, HIGH);
}

void LCD::sendDigit(int digit)
{
    int digitBits = getBits(digit);

    digitalWrite(com, LOW);
    digitalWrite(reset_n, HIGH);
    digitalWrite(latch, HIGH);

    for (int i=0; i<BITS_PER_DIGIT; ++i) {
        digitalWrite(data, digitBits & 0x1);
        clkTick();
        digitBits >>= 1;
    }

    digitalWrite(latch, LOW);

    digitalWrite(com, HIGH);
    clkTick();
    digitalWrite(com, LOW);
}

void LCD::writeDigit(int digit)
{
    clear();
    sentDigit(digit);

void LCD::writeTwoDigits(int digit1, int digit2)
{
    clear();
    sentDigit(digit);
    sendDigit
}
