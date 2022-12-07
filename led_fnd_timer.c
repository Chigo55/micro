#include <mega128.h>

unsigned char led[10] = {0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00};
unsigned char count;

char sec, s10, s1 = 0;
char seg_part[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void timer_out(void);

void main(void)
{
    DDRC = 0xff;
    PORTC = led[0];

    DDRB = 0xff;
    DDRF = 0xff;

    TCNT0 = 100;
    TIMSK = 0x01;
    TCCR0 = 0x07;
    SREG = 0x80;    
    
    timer_out();
}

interrupt [TIM0_OVF] void timer_int0(void)
{
    count++;
    TCNT0 = 100;

    if (count == 100)
    {
        count = 0;
        sec++;
    }
}

void timer_out(void)
{
    s10 = sec/10;
    s1 = sec%10;

    PORTF = 0xef;
    PORTB = seg_part[s1];
    PORTC = led[s10];
    if (sec == 90) sec = 0;

}