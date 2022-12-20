#include <mega128.h>
#include <delay.h>

// 1-2상 여자 방식 모터 구동 배열
// 1-2상 여자 방식 모터 구동 배열 시계방향
unsigned char CW[8] = {0x09, 0x01, 0x05, 0x04, 0x06, 0x02, 0x0a, 0x08};
// 1-2상 여자 방식 모터 구동 배열 반시계방향
unsigned char CCW[8] = {0x08, 0x0a, 0x02, 0x06, 0x04, 0x05, 0x01, 0x09};
// 모터 회전 방향 변수 전역 변수로 선언
char motor_mod;

// 모터 회전 방향 설정 변수 포인터로 선언
// 포인터로 선언하면 메모리의 용량이 가변으로 설정되어 메모리 절약 가능
unsigned char *CW_CCW;

void main(void)
{
    // i, n 지역 변수 선언
    unsigned char i, n;

    // PORTA 전체 출력으로 설정
    DDRA = 0xff;
    // PORTC 전체 출력으로 설정
    DDRC = 0xff;
    // PORTC의 led 전부 off
    PORTC = 0xff;

    // 모터 회전 방향 변수 0으로 설정
    motor_mod = 0;
    // 모터 회전 반향 시계방향으로 설정
    CW_CCW = CW;

    // 지역 인터럽트 4번 허용
    EIMSK = 0x10;
    // 인터럽트 4번 하강에지 사용
    EICRB = 0x02;
    //전역 인터럽트 허용
    SREG = 0x80;

    // 인터럽트 대기 동안 모터 시계방향으로 회전
    while (1)
    {
        for (n = 0;n < 50; n++)
        {
            for (i = 0; i < 8; i++)
            {
                // PORTA에 연결된 모터 포인터에 저장된
                // 배열에 따라 시계방향으로 회전 
                PORTA = *(CW_CCW + i);
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
    // 모터 회전 방향 변수가 0일 경우
    if (motor_mod == 0)
    {   
        // 모터 반시계 방향으로 설정
        CW_CCW = CCW;
        // 모터 회전 방향 변수 1로 설정
        motor_mod = 1;
    }
    // 모터 회전 방향 변수가 0이 아닐 경우
    else
    {
        // 모터 시계 방향으로 설정
        CW_CCW = CW;
        // 모터 회전 방향 변수 0으로 설정
        motor_mod = 0;
    }
    
}