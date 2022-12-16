#include <mega128.h>
#include <Delay.h>

char seg_part[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void main(void)
{
    DDRB = 0xff;
    DDRF = 0xf0;
    DDRE = 0x00;

    PORTF = 0xe0;

    SREG = 0x80;
    EICRB = 0xaa;
    EIMSK = 0xf0;

    while (1) PORTB = 0x3f;
}

interrupt [EXT_INT4] void ext_int4(void)
{
    PORTF = 0xe0;
    PORTB = seg_part[4];
}

interrupt [EXT_INT5] void ext_int5(void)
{
    PORTF = 0xd0;
    PORTB = seg_part[5];
}

interrupt [EXT_INT6] void ext_int6(void)
{
    PORTF = 0xb0;
    PORTB = seg_part[6];
}

interrupt [EXT_INT7] void ext_int7(void)
{
    PORTF = 0x70;
    PORTB = seg_part[7];
}