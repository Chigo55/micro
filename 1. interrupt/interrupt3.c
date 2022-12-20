#include <mega128.h>
#include <Delay.h>

// led 전역 변수로 선언, lsb on
unsigned char led = 0xfe;

void main(void)
{
    // PORTC 전부 출력으로 설정
    DDRC = 0xff;
    // PORTC 전부 입력으로 설정
    DDRE = 0x00;
    // PORTC에 led 출력
    PORTC = led;

    // 전역 인터럽트 허용
    SREG = 0x80;
    // 인터럽트 4번 상승에지 사용
    EICRB = 0x03;
    // 지역 인터럽트 4번 허용
    EIMSK = 0x10;

    // 인터럽트 대기
    while (1);
}

// 인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드 실행
interrupt [EXT_INT4] void ext_int4(void)
{
    //led 1bit씩 왼쪽으로 shift
    led <<= 1;
    // lsb 처음 이외에 항상 off
    led |= 0x01;

    // 모든 led가 꺼지면 다시 lsb on
    if ( led == 0xff) led = 0xfe;

    // PORTC에 led 출력
    PORTC = led;
    // 100ms 동안 대기
    delay_ms(100);
}