#include <mega128.h>
#include <delay.h>

unsigned char CW[4] = {0x01, 0x04, 0x02, 0x08};
unsigned char CCW[4] = {0x08, 0x02, 0x04, 0x01};
char motor_mod;

unsigned char *CW_CCW;

void main(void)
{
    unsigned char i, n;

    DDRA = 0xff;
    DDRC = 0xff;

    motor_mod = 0;
    CW_CCW = CW;

    EIMSK = 0x10;
    EICRB = 0x02;
    SREG = 0x80;
    while (1)
    {
        for (n = 0;n < 12; n++)
        {
            for (i = 0; i < 4; i++)
            {
                PORTA = *(CW_CCW + i)
                delay_ms(100);
            }
        }
        PORTC = PORTC 
    }
}
