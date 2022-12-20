#include <mega128.h>
#include <delay.h>

// 1상 여자 방식 모터 구동 배열
unsigned char CW[4] = {0x01, 0x04, 0x02, 0x08};
// i, n 전역 변수 선언
unsigned char i, n = 0;

void main(void)
{
    // PORTA 전체 출력으로 설정
    DDRA = 0xff;
    // PORTC 전체 출력으로 설정
    DDRC = 0xff;
    // PORTC의 led 전부 off
    PORTC = 0xff;

    // 인터럽트 4, 5번 하강에지 사용
    EICRB = 0x0a;
    // 지역 인터럽트 4, 5번 허용 
    EIMSK = 0x30;
    // 전역 인터럽트 허용
    SREG = 0x80;

    // 인터럽트 대기 동안 모터 시계 방향으로 회전
    while (1)
    {
        // 7.5도 씩 회전, 7.5 * 4 * 12 = 360 
        for (n = 0; n < 12; n++)
        {
            for (i = 0; i < 4; i++)
            {
                // PORTA에 연결된 모터가 배열에 따라 시계방향 회전
                PORTA = CW[i];
                // 100ms 동안 대기, 값이 작을 경우 모터 탈주
                delay_ms(100);
            }

        }
        // XOR을 사용하여 led 반전
        PORTC = PORTC ^ 0xff;
        // 500ms 동안 대기
        delay_ms(500);
    }

}

// 인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드 실행
interrupt [EXT_INT4] void ext_int4(void)
{
    // PORTA에 연결된 모터 배열에 따라 시계방향 회전
    PORTA = CW[i];
    // XOR을 사용하여 led 반전
    PORTC = PORTC ^ 0xff;
    // 500ms 동안 대기
    delay_ms(500);
}
    
interrupt [EXT_INT5] void ext_int5(void)
{
    // PORTA에 연결된 모터 배열을 거꾸로 읽어 반시계방향 회전
    PORTA = CW[3-i];
    // XOR을 사용하여 led 반전
    PORTC = PORTC ^ 0xff;
    // 500ms 동안 대기
    delay_ms(500);
}