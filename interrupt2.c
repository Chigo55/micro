#include <mega128.h>
#include <Delay.h>

void main(void)
{
    unsigned char led = 0xfe;

    DDRC = 0xff;
    DDRE = 0xd07;
    
    SREG = 0x80;
    EICRB = 0x02;
    EIMSK = 0x10;

    while (1)
    {
        do
        {
            PORTC = led;
            delay_ms(100);
            led <<= 1;
            led |= 0x01;
        }
        while (led != 0x7f);

        do
        {
            PORTC = led;
            delay_ms(100);
            led >>= 1;
            led |= 0x80;
        }
        while (led != 0xfe); 
    }
    
}

interrupt [EXT_INT4] void ext_int4(void)
{
    PORTC = 0;
    delay_ms(100);
}