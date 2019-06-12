/* 

    The MIT License (MIT)

    Copyright (c) 2014-2015 almasaeed2010

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  File:   	lcd_Display.h
  Author: 	Renato Ferrarezi - renatoferrarezi@gmail.com
  Comments: universal lcd 16x2 4 bits display routine
  Revision history: 1.0 - first version
  
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LiquidCrystal_h
#define LiquidCrystal_h

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed int int16_t;
typedef unsigned int uint16_t;
typedef signed long int int32_t;
typedef unsigned long int uint32_t;

//typedef bool boolean;
typedef uint8_t byte;
typedef unsigned int word;
typedef uint8_t size_t;



// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x08
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x80
#define LCD_NOBACKLIGHT 0x00

#define LCDEn 0x20  // Enable bit
#define LCDRs 0x10  // Register select bit

    void LiquidCrystal(uint8_t lcd_cols, uint8_t lcd_rows, uint8_t lcdmode, uint8_t dotsize);
    void LCDInit();
    void LCDclear();
    void LCDhome();
    void LCDsetCursor(uint8_t col, uint8_t row);
    void LCDDisplayOff();
    void LCDdisplayOn();
    void LCDCursorOff();
    void LCDcursorOn();
    void LCDBlinkOff();
    void LCDblinkOn();
    void LCDscrollDisplayLeft();
    void LCDscrollDisplayRight();
    void LCDleftToRight();
    void LCDrightToLeft();
    void LCDautoscroll();
    void LCDnoAutoscroll();
    void LCDcreateChar(uint8_t location, uint8_t charmap[]);
    void LCDnoBacklight(void) ;
    void LCDbacklight(void) ;
       
    extern void phi_lcd_send(uint8_t);			//**** you must implement this function for the physical layer for communication ****
    extern void LCDdelay_us(unsigned long);		//**** use the delay routine available in your environment ****

    unsigned char _displayfunction;
    unsigned char _displaycontrol;
    unsigned char _displaymode;
    unsigned char _numlines;
    unsigned char _cols;
    unsigned char _rows;
    unsigned char _backlightval;


#endif	/* XC_HEADER_TEMPLATE_H */

