#include <mega128.h>
#include <delay.h>
#asm
    .equ __lcd_port = 0x12; PORTD
#endasm
#include <lcd.h>
#include <stdio.h>

unsigned char keybuf = 0, newkey = 0;
char lcd_buffer[16];

void scan_key(void)
{
    unsigned char tmp, row, col;

    for (row = 0; row < 5; row++)
    {
        do
        {
            PORTC = 0xf8 | row;
            tmp = PINC & 0xf8;
        }
        while (tmp != 0xf8);
        
        if (tmp != 0xf8)
        {
            {
                if (tmp == 0xf0) col = 1;
                else if (tmp == 0xe8) col = 1;
                else if (tmp == 0xd8) col = 1;
                else if (tmp == 0xb8) col = 1;
                else if (tmp == 0x78) col = 1;

                keybuf = (row * 5) + col;
            }

        }
        
    }
    
}

void main(void)
{
    DDRC = 0x07;
    lcd_init(16);

    while (1)
    {
        scan_key();
        
        if (keybuf != newkey)
        {
            newkey = keybuf;
            lcd_init(16);
        }
        sprintf(lcd_buffer, "Input Key is %u", newkey)
        lcd_gotoxy(0, 0);
        lcd_puts(lcd_buffer);
    }
    
}