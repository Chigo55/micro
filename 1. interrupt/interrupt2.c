#include <mega128.h>
#include <Delay.h>

void main(void)
{
    //led 초기값 -> lsb led On
    unsigned char led = 0xfe;

    // PORTC 전체를 출력으로 설정
    DDRC = 0xff;
    // PORTE 상위 4bit를 입력으로 설정
    DDRE = 0x0f;
    // PORTC에 led를 출력
    PORTC = led;
    
    // 전역 인터럽트 허용
    SREG = 0x80;
    // 인터럽트 4번 하강에지 사용
    EICRB = 0x02;
    // 지역 인터럽트 4번 허용
    EIMSK = 0x10;

    while (1)
    {
        //while문을 만족하는 동안 do문의 내용을 반복적으로 실행
        do
        {
            // PORTC에 led 출력
            PORTC = led;
            // 100ms 동안 대기
            delay_ms(100);
            // led 1bit씩 왼쪽으로 shift
            led <<= 1;
            // lsb를 처음 이외에 항상 off
            led |= 0x01;
        }
        while (led != 0x7f);

        //while문을 만족하는 동안 do문의 내용을 반복적으로 실행
        do
        {
            // PORTC에 led 출력
            PORTC = led;
            // 100ms동안 대기
            delay_ms(100);
            // 오른쪽으로 shift
            led >>= 1;
            // msb를 처음 이외에 항상 off
            led |= 0x80;
        }
        while (led != 0xfe); 
    }
    
}

// 인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드를 실행
interrupt [EXT_INT4] void ext_int4(void)
{
    // PORTC의 모든 led on
    PORTC = 0;
    // 100ms동안 대기
    delay_ms(100);
}