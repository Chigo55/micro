#include <mega128.h>
#include <delay.h>

unsigned char CW[4] = {0xfc, 0xf0, 0xc0, 0x00};
unsigned char i;

char rx;

void main(void)
{
    UCSR0A = 0;
    UCSR0B = 0x98;
    UCSR0C = 0x06;

    UBRR0H = 0;
    UBRR0L = 103;
    SREG = 0x80;

    DDRC = 0xff;
    PORTC = 0xff;
}

interrupt [USART0_RXC] usart_rx(void)
{
    rx = UDR0;

    if (rx == "a")
    {
        for (i = 0; i < 12; i++)
        {
            for (i = 0; i < 4; i++)
            {
                PORTC = CW[i];
                delay_ms(50);
            }
            delay_ms(50);
        }
        delay_ms(50);
    }

    if (rx == "s")
    {
        for (i = 0; i < 12; i++)
        {
            for (i = 0; i < 4; i++)
            {
                PORTA = CW[3-i];
                delay_ms(50);
            }
            delay_ms(50);
        }
        delay_ms(50);
    }
    
}