#include <mega128.h>
#include <delay.h>

char Usart0_Rx(void);

unsigned char CW[4] = {0x09, 0x05, 0x06, 0x0a};
unsigned char CCW[4] = {0x0a, 0x06, 0x05, 0x09};

unsigned char *CW_CCW;
unsigned char m, n, i;

char rx;

void main(void)
{
    UCSR0A = 0;
    UCSR0B = 0x98;
    UCSR0C = 0x06;

    UBRR0H = 0;
    UBRR0L = 103;
    SREG = 0x80;

    DDRA = 0xff;
    DDRC = 0xff;
    PORTC = 0xff;

    while (1)
    {
        if (Usart0_Rx() == "a")
        {
            CW_CCW = CCW;

            for (i = 0; i < 12; i++)
            {
                for (i = 0; i < 4; i++)
                {
                    PORTA = *(CW_CCW + i);
                    delay_ms(30);
                }
                PORTC = PORTC ^ 0xff;
                delay_ms(50);
            }
            delay_ms(50);
        }

        if (Usart_Rx() == "s")
        {
            CW_CCW = CW;

            for (i = 0; i < 12; i++)
            {
                for (i = 0; i < 4; i++)
                {
                    PORTA = *(CW_CCW + i);
                    delay_ms(30);
                }
                PORTC = PORTC ^ 0xff;
                delay_ms(100);
            }
            delay_ms(5000);
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