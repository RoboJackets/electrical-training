#ifndef LCD_H_
#define LCD_H_

class LCD {
    // Default constructor
    LCD();
    // Constructor for LCD
    LCD(int, int, int, int, int, int);
    
    // Set all shift register values to 0
    void clear();
    // Send encoding for one digit to the LCD
    void sendDigit(int);

    // Clear the LCD and display one digit
    void writeDigit(int);
    // Clear the LCD and display two digits
    void writeTwoDigits(int, int);

    // Get the encoding for a digit between 0 and 9
    int getBits(int);

    // Utility to tick the clock once
    void clkTick();

    // Pins connecting to shift registers and LCD
    int com, oe_n, latch, clk, reset_n, data;

    const int BITS_PER_DIGIT = 8;
    const int TOTAL_BITS = 4 * BITS_PER_DIGIT;
    const int DELAY_HALF_PERIOD = 10;
};
#endif /* LCD_H_ */
