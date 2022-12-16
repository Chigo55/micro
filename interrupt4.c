#include <mega128.h>
#include <Delay.h>

char seg_part[4] = {0x66, 0x6d, 0x7d, 0x07};

void main(void)
{
    DDRE = 0x00;
    DDRB = 0xff;
    DDRF = 0xf0;

    PORTF = 0xe0;
    PORTB = 0x3f;

    SREG = 0x80;
    EICRB = 0xaa;
    EIMSK = 0xf0;

    while (1);
}

interrupt [EXT_INT4] void ext_int4(void)
{
    PORTB = seg_part[0];
}

interrupt [EXT_INT5] void ext_int5(void)
{
    PORTB = seg_part[1];
}

interrupt [EXT_INT6] void ext_int6(void)
{
    PORTB = seg_part[2];
}

interrupt [EXT_INT7] void ext_int7(void)
{
    PORTB = seg_part[3];
}