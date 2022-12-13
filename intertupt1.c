#include <mega128.h>

// led 초기값-> 맨 왼쪽 led on
unsigned char led = 0b11111110; 

void main(void)
{
    // PORTC 전체를 출력으로 설정
    DDRC = 0xff; 
    // PORTE 상위 4bit를 입력으로 설정
    DDRE = 0x0f;
    // led를 PORTC로 출력
    PORTC = led;

    // 전역 인터럽트 허용
    SREG = 0x80;
    // 인터럽트 4번을 하강에지로 사용
    EICRB |= 0x02;
    // 인터럽트 4번을 개별적으로 허용
    EIMSK |= 0x10;
    // 인터럽트 대기
    while(1);
}

// 인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드 실행
interrupt [EXT_INT4] void int4(void)
{
    // led를 1bit씩 shift
    led <<= 1;
    // lsb를 처음 이외에는 계속 off
    led |= 0x01;

    // led가 모두 꺼지면 다시 lsb를 켠다.
    if(led == 0xff) led = 0x01;
    // led를 PORTC로 출력
    PORTC = led;
}