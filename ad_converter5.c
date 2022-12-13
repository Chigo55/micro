#include <mega128.h>
#include <delay.h>
#include <stdio.h>

#asm
    .equ_lcd_port = 0x12;
#endasm

#include <lcd.h>

#define ADC_VREF_TYPE 0x03

unsigned int read_adc(unsigned char adc_input)
{
    ADMUX = adc_input|ADC_VREF_TYPE;
    ADCSRA |= 0x40;

    while ((ADCSRA & 0x10) == 0);
    ADCSRA |= 0x10;
    return ADCW;
}

void main(void)
{
    int adc_val;
    char text[16];
    float temp;

    ADMUX = ADC_VREF_TYPE;
    ADCSRA = 0x86;
    SFIOR &= 0xef;

    lcd_init;

    while (1)
    {
        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_puts("LM35 Temperature")

        adc_val = read_adc(0);

        temp = adc_val * 0.0048828125 * 10;

        sprintf(text, "TEMP = %4.2f \xdfC 0", temp);
        lcd_gotoxy(0, 1);
        lcd_puts(text);
        delay_ms(1000);
    }
    
}