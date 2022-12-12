#include <mega128.h>
#include <delay.h>

unsigned char CW[4] = {0x01, 0x04, 0x02, 0x08};

unsigned char *CW_CCW;

void main(void)
{
    unsigned char i, n = 0;

    DDRA = 0xff;
    DDRC = 0xff;

    CW_CCW = CW;

    while (n < 24)
    {
        for (n = 0;n < 12; n++)
        {
            for (i = 0; i < 4; i++)
            {
                PORTA = *(CW_CCW + i)
                delay_ms(100);
            }

        }
        PORTC = PORTC ^ 0xff;
        delay_ms(500);
        
        for (n = 12; n < 24; n++)
        {
            for (i = 0; i < 4; i++)
            {
                PORTA = *(CW_CCW + (3 - i))
                delay_ms(100);
            }

        }
        PORTC = PORTC ^ 0xff;
        delay_ms(500);
    }

}

interrupt [EXT_INT4] void ext_int4(void)
{
    if (motor_mod == 0)
    {
        CW_CCW = CCW;
        motor_mod = 1;
    }
    else
    {
        CW_CCW = CW;
        motor_mod = 0;
    }
    
}