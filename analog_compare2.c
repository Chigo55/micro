#include <mega128.h>
#include <delay.h>

char seg[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void main(void)
{
    char led = 0xfe;

    int i, s1, s10 = 0;

    DDRC = 0xff;
    DDRB = 0xff;
    DDRF = 0xf0;
    DDRE = 0x02;

    ACSR = 0x00;
    SFIOR = 0x00;

    PORTC = led;

    while (1)
    {
        for (i = 0; i < 100; i++)
        {
            PORTF = 0xd0;
            PORTB = seg[s10];
            delay_ms(5);

            PORTF = 0xe0;
            PORTB = seg[s1];
            delay_ms(5);
        }

        if (ACSR & 0x20)
        {
            s1++;
            if (s1 == 10) s1 = 0,s10++;
            if (s10 == 10) s10 = 0;

            led <<= 1;
            led |= 0x01;

            if (led == 0xff) led = 0xfe;
            PORTC = led;
        }
        
    }

}