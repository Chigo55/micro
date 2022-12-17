#include <mega128.h>
#include <Delay.h>

char seg_part[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned char keybuf = 0, newkey = 0;
unsigned char n10 = 0, n1 = 0;

void scan_key(void);

void main(void)
{
    DDRC = 0x07;
    DDRB = 0xff;
    DDRF = 0xf0;

    while (1)
    {
        scan_key();
        newkey = keybuf;

        n10 = newkey / 10;
        n1 = newkey % 10;

        PORTF = 0xe0;
        PORTB = seg_part[n1];
        delay_ms(5);

        PORTF = 0xd0;
        PORTB = seg_part[n10];
        delay_ms(5);
    }
    
}

void scan_key(void)
{
    char row, col, tmp;

    for (row = 0; row < 5; row++)
    {
        do
        {
            PORTC = 0xf8; | row;
            tmp = PINC & 0xf8;
        } 
        while (tmp != (PINC & 0xf8));

        if (tmp != 0xf8)
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
