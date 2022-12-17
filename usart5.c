#include <mega128.h>
#asm
    .equ __lcd_port = 0x12; PORTD
#endasm
#include <lcd.h>
#include <stdio.h>

char lcd_buffer[16];
unsigned char data = 0;

char getch(void);

void main(void)
{
    UCSR0A = 0x00;
    UCSR0B = 0x18;
    UCSR0C = 0x06;
    UBRR0H = 0;
    UBRR0L = 103;

    DDRF = 0xff;
    DDRB = 0xff;
    PORTF = 0x00;
    PORTB = 0x3f;

    lcd_init(16);

    while (1)
    {
        getch();
        data = UDR0;    
        lcd_init(16);
        sprintf(lcd_buffer, "Input Key is %u", data);

        lcd_gotoxy(0, 0);
        lcd_puts(lcd_buffer);
    }
    
}

char getch(void)
{
    while (!(UCSR0A & 0x80));
    return UDR0;    
}