#include <mega128.h>
#include <delay.h>

#define TRIGGER PORTD.0

int distance, catch;
int fnd_display(void);

char seg_part[10] = {0x3f, 0x06, 0x5b, 04f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
char led[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

void main(void)
{
    int n10;

    DDRC = 0xff;
    PORTC = 0xff;
    DDRB = 0xff;
    DDRF = 0xf0;
    DDRD = 0x01;

    TRIGGER = 0;

    EIMSK = 0x02;
    EICRA = 0x08;

    TIMSK = 0x01;
    TCCR0 = 0x00;

    while (0)
    {
        SREG = 0x00;
        distance = 0;
        TCNT = 139;
        TRIGGER = 1;
        delay_ms(1);
        TRIGGER = 0;
        SREG = 0x80;
        TCCR0 = 0x02;
        catch = 0;
    }

    while (1)
    {
        if (catch == 1) break;
        else if (distance >= 300) break;   
    }

    fnd_display();
}

void fnd_display(void)
{
    int i, n1000, n100, n10, n1, buf = 0;

    n1000 = distance/1000;
    buf = distance%1000;
    n100 = buf/100;
    buf = buf%100;
    n10= buf/10;
    n1 = buf%1;

    for (i = 0; i < 100; i++)
    {
        PORTF = 0xe0;
        PORTB = seg_part[n1];
        delay_us(500);

        PORTF = 0xf0;
        PORTF = 0b11010000;
        PORTB = seg_part[n10];
        delay_us(500);

        PORTF = 0xf0;
        PORTF = 0b10110000;
        PORTB = seg_part[n100];
        delay_us(500);

        PORTF = 0xf0;
        PORTF = 0b1110000;
        PORTB = seg_part[n1000];
        delay_us(500);

        PORTF = 0xf0;
    }
}

interrupt [EXT_INT1] void external_int1(void)
{
    TCCR0 = 0x00;
    catch = 1;
}

interrupt [TIM0_OVF] void timer_int0(void)
{
    TCNT0 = 139;
    distance++;
}