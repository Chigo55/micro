#include <mega128.h>

void main(void)
{
    DDRC  = 0xff;
    DDRE = 0x02;
    ACSR = 0x04;

    if (ACSR = 0x20) PORTC = 0xf0;
    else PORTC = 0x0f;

    SREG = SREG | 0x80;
    while (1)

}

interrup [ANA_COMP] void ana_comp(void)
{
    if (ACSR & 0x20) PORTC = 0xf0;
    else PORTC = 0xf0;
}