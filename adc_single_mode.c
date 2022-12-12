#include <mega128.h>
#include <delay.h>

char seg_part[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void AD_display(int);

void main(void)
{
    int ad_val;

    DDRB = 0xff;
    DDRF = 0xf0;

    ADMUX = 0x00;
    ADCSRA = 0x87;
    delay_ms(5);

    while (1)
    {
        ADCSRA = 0xc7;
        while ((ADCSRA & 0x10) == 0);
        
        ad_val = (int)ADCL + ((int)ADCH << 8);
        AD_display(ad_val);        
    }
}

void AD_display(int val)
{
    float fval;
    int ival, buf;
    char n100, n10, n1;

    fval = (float)val * 5.0 / 1023.0;
    ival = (int)(fval * 100.0 + 0.5);

    n100 = buf / 100;
    buf = buf % 100;

    n10 = buf / 10;
    n1 = buf % 10;

    PORTF = 0xe0;
    PORTB = seg_part[n1];
    delay_ms(5);

    PORTF = 0xd0;
    PORTB = seg_part[n10];
    delay_ms(5);

    PORTF = 0xb0;
    PORTB = seg_part[n100];
    delay_ms(5);
}