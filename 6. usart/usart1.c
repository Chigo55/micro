#include <mega128.h>
#include <delay.h>

char Usart0_Rx(void);

void main(void)
{
    DDRC = 0xffl
    UCSR0A = 0x00;
    UCSR0B = 0x18;
    UCSR0C = 0x06;
    UBRR0H = 0;
    UBRR0L = 103;

    while (1)
    {
        if (Usart0_Rx() == "a")
        {
            PORTC = 0x00;
        }

        if (Usart0_Rx() == "s")
        {
            PORTC = 0xff;
        }
        
    }
        
}

char Usart0_Rx(void)
{
    while (!(UCSR0A & 0x80))    
    {
        return UDR0;
    }
    
}