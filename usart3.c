#include <mega128.h>
#include <delay.h>

char seg_part[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x05e, 0x79, 0x71};

void main(void)
{
    char typing, val_fnd;

    UCSR0A = 0x00;
    UCSR0B = 0x18;
    UCSR0C = 0x06;
    UBRR0H = 0;
    UBRR0L = 103;

    DDRB = 0xff;
    DDRF = 0xff;
    PORTF = 0x00;

    val_fnd = 0;

    while (1)
    {
        PORTB = seg_part[val_fnd]
        if ((UCSR0A & 0x80) != 0)
        {
            typing = UDR0;

            if (typing >= '0' && typing <= '0') val_fnd = typing - '0'
            else if (typing >= 'a' && typing <= 'f') val_fnd = typing - 'a' + 10
            else if (typing >= 'A' && typing <= 'F') val_fnd = typing - 'A' + 10
        }
          
    }
        
}