#include <mega128.h>

unsigned char led = 0xfe;

void main(void)
{
    DDRC = 0xff;
    PORTC = led;

    TIMSK = 0x02;
    TCCR0 = 0x67;
    OCR0 = 255;
    TCNT0 = 0;
    SREG = 0x80;
}

interrupt [TIM0_COMP] void timer_comp2(void)
{
    led <<= 1;
    led |= 0x01;

    if (led == 0xff) led = 0xfe;
    PORTC = led;
}