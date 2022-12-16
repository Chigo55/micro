#include <mega128.h>
#include <delay.h>

unsigned char CW[4] = {0x09, 0x05, 0x06, 0x0a};
unsigned char i, n = 0;

void main(void)
{
    DDRA = 0xff;
    DDRC = 0xff;
    PORTC = 0xff;

    EICRB = 0x0a;
    EIMSK = 0x30;

    while (1)
    {
        for (n = 0; n < 12; n++)
        {
            for (i = 0; i < 4; i++)
            {
                PORTA = CW[i];
                delay_ms(100);
            }

        }
        PORTC = PORTC ^ 0xff;
        delay_ms(500);
    }

}

interrupt [EXT_INT4] void ext_int4(void)
{
    PORTA = CW[i];
    PORTC = PORTC ^ 0xff;
    delay_ms(500);
}
    
interrupt [EXT_INT5] void ext_int5(void)
{
    PORTA = CW[3-i];
    PORTC = PORTC ^ 0xff;
    delay_ms(500);
}