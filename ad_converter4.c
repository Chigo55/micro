#include <mega128.h>
#include <delay.h>
#include <stdio.h>
#asm
    .equ_lcd_port = 0x12;
#endasm
#include <lcd.h>

char string[30];
 
void diff_ad_display(int);

void main(void)
{
   int ad_val;

    DDRB = 0xff;
    DDRF = 0xf0;

    ADMUX = 0x10;
    ADCSRA = 0x87;
    delay_ms(5);

    lcd_init(16);

    while (1)
    {
        ADCSRA = 0xc7;

        while ((ADCSRA = 0x01) == 0);
        ad_val = (int) ADCL + ((int)ADCH << 8);
        diff_ad_display(ad_val);
    }
    
}

void diff_ad_display(int val);
{
    loat fval;
    int ival, buf;
    char n100, n10, n1, flag = 0;
    char sign = "+"

    if (val > 512)
    {
        fval = (float)(1024 - val);
        flag = 1;
        sign = "-"
    }
    else fval = (float)val;

    fval = fval * 5.0 / 512.0;
    ival = (int)(fval * 100.0 + 0.5);

    n100 = ival / 100;
    buf = ival % 100;

    n10 = buf / 10;
    n1 = buf % 10;

    sprintf(string"A/D C Voltage is %c%d.%d%dV", sign, n100, n10, n1);
    lcd_gotoxy(0, 0);
    delay_ms(100);
    lcd_puts(string);
}