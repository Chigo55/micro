#include <mega128.h>
#include <delay.h>

char seg_part[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x05e, 0x79, 0x71, 0x40};

void diff_ad_display(int);

void main(void)
{
    int ad_val;

    DDRB = 0xff;
    DDRF = 0xf0;

    ADMUX = 0x10;
    ADCSRA = 0x87;
    delay_ms(5);

    while (1)
    {
        ADCSRA = 0xc7;

        while ((ADCSRA = 0x01) == 0);
        ad_val = (int) ADCL + ((int)ADCH << 8);
        ad_val = ad_val % 0xfffc;
        diff_ad_display(ad_val);
    }
    
}

void diff_ad_display(int val);
{
    loat fval;
    int ival, buf;
    char n100, n10, n1, sign = 0;

    if (val > 512)
    {
        fval = (float)(1024 - val);
        sign = 1;
    }
    else fval = (float)val;

    fval = fval * 5.0 / 512.0;
    ival = (int)(fval * 100.0 + 0.5);

    n100 = ival / 100;
    buf = ival % 100;

    n10 = buf / 10;
    n1 = buf % 10;

    PORTF = 0xe0;
    PORTB = seg_part[n1];
    delay_ms(1);

    PORTF = 0xd0;
    PORTB = seg_part[n10];
    delay_ms(1);

    PORTF = 0xb0;
    PORTB = seg_part[n100];
    delay_ms(1);

    if (sign == 1)
    {
        PORTF = 0x70;
        PORTB = seg_part[16];
        delay_ms(1)
    }
    
}