# Universal_LCD_Routine
Universal LCD 16x2 routine written in C. All LCD control was created except the physical communication, This allows its use in any environment or microcontroller. You only need to create 2 functions:  void phi_lcd_send(uint8_t)  Rotutine to send data on lsb and control in msb to the display.  void LCDdelay_us(unsigned long) Delay routine in microseconds
No guaranties, use at ypur own risc.
