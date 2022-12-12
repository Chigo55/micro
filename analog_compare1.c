#include <mega128.h>
 void delay(unsigned int);

 void main(void)
 {
    char led = 0xfe;

    DDRC = 0xff;
    DDRE = 0x02;

    ACSR = 0x00;
    SFIOR = 0x00;
    
    PORTC = led;
    while (1)
    {
        if (ACSR & 0x20)
        {
            led <<= 1;
            led |= 0x01;
            
            if (led == 0xff) led = 0xfe;

            PORTC = led;
            delay(5);
        }
    }
 }

 void delay(unsigned int cnt)
 {
    unsigned in i, j;

    for ( i = 0; i < cnt; i++)
    {
        j = 60000;
        while (j--);        
    }
    
 }