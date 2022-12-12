#include <mega128.h>

unsigned char led = 0xfe;
unsigned char count = 0;

void main(void)
{
    DDRC = 0xff;
    PORTC = led;

    TCNT0 = 0;
    TIMSK = 2;
    TCCR0 = 0x0f;
    SREG = 0x80;
    OCR0 = 255;
}

interrupt [TIM0_COMP] timer0_comp(void)
{
    count++;
    if ( count == 250)
    {
        led <<= 1;
        led |= 0x01;
        
        if (led == 0xff;) led = 0xfe;
        PORTC = led;    
        count = 0;
    }
    
}