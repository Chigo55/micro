#include <mega128.h>
#include <Delay.h>

unsigned char led = 0xfe;

void main(void)
{
    DDRC = 0xff;
    DDRE = 0x00;
    
    PORTC = led;

    SREG = 0x80;
    EICRB = 0x03;
    EIMSK = 0x10;

    while (1);
}

interrupt [EXT_INT4] void ext_int4(void)
{
    led <<= 1;
    led |= 0x01;

    if ( led == 0xff) led = 0xfe;

    PORTC = led;
    delay_ms(100);
}