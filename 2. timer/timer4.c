#include <mega128.h>

// led 전역 변수로 선언, led 초기값 -> lsb on
unsigned char led = 0xfe;


void main(void)
{
    // PORTC 전체 출력으로 설정
    DDRC = 0xff;
    // PORTC에 led 출력
    PORTC = led;

    // 지역 Timer0 oc로 사용
    TIMSK = 0x02;
    // 위상교정 PWM mode, 분주비 1024
    TCCR0 = 0x67;
    // oc 레지스터 255로 설정
    OCR0 = 255;
    // Timer0 TCNT 시작값 0으로 설정
    TCNT0 = 0;
    // 전역 인터럽트 허용
    SREG = 0x80;
}

// 인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드 실행
interrupt [TIM0_COMP] void timer_comp2(void)
{
    // led 왼쪽으로 1bit씩 shift
    led <<= 1;
    // lsb 처음 이외에는 항상 off
    led |= 0x01;

    // 모든 led가 꺼지면 lsb on
    if (led == 0xff) led = 0xfe;
    // PORTC에 led 출력
    PORTC = led;
}