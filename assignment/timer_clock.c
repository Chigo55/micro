#include <mega128.h>
#include <delay.h>

char seg_part[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
char n1, n10, n100, n1000 = 0;
char pos = 0;
char hour, min, sec = 0;
char count = 0;

void timer_out(void);

void main(void)
{
    DDRB = 0xff;
    DDRF = 0xf0;

    EICRB = 0x0a;
    EIMSK = 0x30;
    TIMSK = 1;
    TCCR0 = 0x07;
    TCNT = 0;

    SREG = 0x80;

    while (1)
    {
        timer_out();
         if (count >= 61)
         {
            count = 0;
            sec = sec + 1;

            if (sec == 60)
            {
                sec = 0;
                min = min + 1;

                if (min == 60)
                {
                    min = 0;
                    hour = (hour + 1) % 24;
                }
                
            }
            
        }
         
    }

}

void timer_out(void)
{
    PORTF = 0xe0;
    PORTB = seg_part[min % 10];
    delay_ms(3);

    PORTF = 0xd0;
    PORTB = seg_part[min / 10];
    delay_ms(3);

    PORTF = 0xb0;
    PORTB = seg_part[hour % 10];
    delay_ms(3);

    PORTF = 0x70;
    PORTB = seg_part[hour / 10];
    delay_ms(3);

    if (count <= 30)
    {
        PORTF = 0xe0;
        PORTB = seg_part[min % 10];
        delay_ms(3);
    }
    
}

interrupt [EXT_INT4] void ext_int4(void)
{
    if (pos == 0) n1 = (n1 + 1) % 10;
    else if (pos == 1) n10 = (n10 + 1) % 6;
    else if (pos == 2)
    {
        if (n1000 == 2) n100  = (n100 + 1) % 4;
        else n100 = (n100 + 1) % 10;
    }
    else
    {
        if (n100 >= 4) n1000 = (n1000 +1 ) % 2;
        else n100 = (n1000 + 1) % 3;
    }
    hour = n1000 * 10 + n100;
    min = n10 * 10 + n1;
}

interrupt [EXT_INT5] void ext_int5(void)
{
    pos = (pos + 1) % 4;
}

interrupt [TIM0_OVF] void timer0_int(void)
{
    count++;
}