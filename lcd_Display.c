/*    The MIT License (MIT)

    Copyright (c) 2014-2015 almasaeed2010

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
	to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
	and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
	IN THE SOFTWARE.

  File:   	lcd_Display.h
  Author: 	Renato Ferrarezi - renatoferrarezi@gmail.com
  Comments: universal lcd 16x2 4 bits display routine
  Revision history: 1.0 - first version
  
*/

#include "lcd_Display.h"

void LiquidCrystal(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t lcdmode, uint8_t dotsize) {
    _cols = lcd_cols;
    _rows = lcd_rows;
    _backlightval = LCD_NOBACKLIGHT;
    
    _displayfunction = lcdmode | LCD_1LINE | LCD_5x8DOTS;

    if (_rows > 1) {
        _displayfunction |= LCD_2LINE;
    }
    _numlines = _rows;

    // for some 1 line displays you can select a 10 pixel high font
    if ((dotsize != 0) && (_rows == 1)) {
        _displayfunction |= LCD_5x10DOTS;
    }
}

void expanderWrite(uint8_t _data) {
    phi_lcd_send(_data | _backlightval);
}

void pulseEnable(uint8_t _data) {
    expanderWrite(_data | LCDEn); // En high
    LCDdelay_us(1); // enable pulse must be >450ns

    expanderWrite(_data & ~LCDEn); // En low
    LCDdelay_us(50); // commands need > 37us to settle
}

void write4bits(uint8_t value) {
    expanderWrite(value);
    pulseEnable(value);
}

void LCDsend(uint8_t value, uint8_t mode) {
    uint8_t highnib = value >> 4;
    uint8_t lownib = value & 0x0F;
    write4bits((highnib) | mode);
    write4bits((lownib) | mode);
}

void LCDcommand(uint8_t value) {
    LCDsend(value, 0);
}

void LCDwrite(uint8_t value) {
    LCDsend(value, LCDRs);
}

void LCDInit() {
  
    // Now we pull both RS and R/W low to begin commands
    expanderWrite(_backlightval); // reset expanderand turn backlight off (Bit 8 =1)
    LCDdelay_us(1000);

    //put the LCD into 4 bit mode
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03);
    LCDdelay_us(4500); // wait min 4.1ms

    // second try
    write4bits(0x03);
    LCDdelay_us(4500); // wait min 4.1ms

    // third go!
    write4bits(0x03);
    LCDdelay_us(150);

    // finally, set to 4-bit interface
    write4bits(0x02);


    // set # lines, font size, etc.
    LCDcommand(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    LCDcommand(LCD_DISPLAYCONTROL | _displaycontrol);

    // clear it off
    LCDclear();

    // Initialize to default text direction (for roman languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

    // set the entry mode
    LCDcommand(LCD_ENTRYMODESET | _displaymode);

    LCDhome();

}

/********** high level commands, for the user! */
void LCDclear() {
    LCDcommand(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
    LCDdelay_us(2000); // this command takes a long time!
}

void LCDhome() {
    LCDcommand(LCD_RETURNHOME); // set cursor position to zero
    LCDdelay_us(2000); // this command takes a long time!
}

void LCDsetCursor(uint8_t col, uint8_t row) {
    int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row > _numlines) {
        row = _numlines - 1; // we count rows starting w/0
    }
    LCDcommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)

void LCDDisplayOff() {
    _displaycontrol &= ~LCD_DISPLAYON;
    LCDcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCDdisplayOn() {
    _displaycontrol |= LCD_DISPLAYON;
    LCDcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off

void LCDCursorOff() {
    _displaycontrol &= ~LCD_CURSORON;
    LCDcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCDcursorOn() {
    _displaycontrol |= LCD_CURSORON;
    LCDcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor

void LCDBlinkOff() {
    _displaycontrol &= ~LCD_BLINKON;
    LCDcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCDblinkOn() {
    _displaycontrol |= LCD_BLINKON;
    LCDcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM

void LCDscrollDisplayLeft() {
    LCDcommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCDscrollDisplayRight() {
    LCDcommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right

void LCDleftToRight() {
    _displaymode |= LCD_ENTRYLEFT;
    LCDcommand(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left

void LCDrightToLeft() {
    _displaymode &= ~LCD_ENTRYLEFT;
    LCDcommand(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor

void LCDautoscroll(void) {
    _displaymode |= LCD_ENTRYSHIFTINCREMENT;
    LCDcommand(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor

void LCDnoAutoscroll(void) {
    _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    LCDcommand(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters

void LCDcreateChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7; // we only have 8 locations 0-7
    LCDcommand(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++) {
        LCDwrite(charmap[i]);
    }
}

// Turn the (optional) backlight off/on

void LCDBacklightOff(void) {
    _backlightval = LCD_NOBACKLIGHT;
    expanderWrite(0);
}

void LCDbacklightOn(void) {
    _backlightval = LCD_BACKLIGHT;
    expanderWrite(0);
}
