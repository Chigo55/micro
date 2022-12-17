#include <mega128.h>

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

    while (1)
    {
        getch();
        PORTB = UDR0;    
    }
    
}

char getch(void)
{
    while (!(UCSR0A & 0x80));
    return UDR0;    
}