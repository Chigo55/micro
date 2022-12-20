#include <mega128.h>
#include <delay.h>

// PORTD의 0번을 trigger로 정의
#define TRIGGER PORTD.0

// distance, catch 전역 변수로 선언
int distance, catch;

// fnd_display 함수 선언
void fnd_display(void);

// fnd 세그먼트 파트 표시 배열(0~9)
char seg_part[10] = {0x3f, 0x06, 0x5b, 04f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void main(void)
{
    // n10 지역 변수 선언
    int n10;

    // fnd 사용을 위한 출력 선언
    // PORTB: fnd 표시를 위한 7-segment led
    // PORTF: fnd 표시를 위한 7-segment 자릿수
    DDRB = 0xff;
    DDRF = 0xf0;
    // PORTD 0번 출력으로 사용
    DDRD = 0x01;

    // trigger에 0 저장
    TRIGGER = 0;

    // 지역 인터럽트 1번 허용
    EIMSK = 0x02;
    // 인터럽트 1번 하강에지 사용
    EICRA = 0x08;

    // 지역 Timer0 ovf로 사용
    TIMSK = 0x01;
    // nomal mode, 클럭 사용X
    TCCR0 = 0x00;

    while (1)
    {
        // 전역 인터럽트 허용X
        SREG = 0x00;
        // 외부 인터럽트 플레그 레지스터 (따로 설정할 필요 없음)
        EIFR = 0xff;
        // 파이머 인터럽트 플레그 레지스터 (따로 설정할 필요 없음)
        TIFR = 0xff;
        // 동기 모드(내부 clk 사용 -> 타이머로 사용)
        ASSR = 0x00;

        // 현재 거리 0으로 저장
        distance = 0;
        // Timer0의 TCNT 시작값 139로 설정
        TCNT0 = 139;
        // trigger에 1 저장 (초음파 발생 시작)
        TRIGGER = 1;
        // 1ms 동안 대기
        delay_ms(1);

        // // trigger에 0 저장 (초음파 발생 중지)
        TRIGGER = 0;
        // 전역 인터럽트 허용
        SREG = 0x80;
        // normal mode, 분주비 2
        TCCR0 = 0x02;
        // catch에 0 저장
        catch = 0;

        // 반사된 초음파가 도달할 때 까지 대기
        while (1)
        {   
            // 반사된 초음파가 도달하면 while문 탈출
            if (catch == 1) break;
            // distance가 300이 될 때 까지 초음파가 도달하지 못하면 while문 탈출
            else if (distance >= 300) break;   
        }
        // fnd_display 함수 콜
        fnd_display();
    }
    
}

// fnd_display 함수 정의
void fnd_display(void)
{
    // i, n1000, n100, n10, n1, buf 지역 변수로 선언, buf는 초기 값을 0으로 저장
    int i, n1000, n100, n10, n1, buf = 0;

    // fnd 표시를 위한 자릿수 분할
    // fnd 1번째 자리 분할
    n1000 = distance/1000;
    buf = distance%1000;
    // fnd 2번째 자리 분할
    n100 = buf/100;
    buf = buf%100;
    // fnd 3번째 자리 분할
    n10= buf/10;
    // fnd 4번째 자리 분할
    n1 = buf%1;

    for (i = 0; i < 100; i++)
    {   
        // fnd 4번째 자리에 분할한 자릿수 표시
        PORTF = 0xe0;
        PORTB = seg_part[n1];
        delay_us(500);
        PORTF = 0xf0;

        // fnd 3번째 자리에 분할한 자릿수 표시
        PORTF = 0b11010000;
        PORTB = seg_part[n10];
        delay_us(500);
        PORTF = 0xf0;

        // fnd 2번째 자리에 분할한 자릿수 표시
        PORTF = 0b10110000;
        PORTB = seg_part[n100];
        delay_us(500);
        PORTF = 0xf0;

        // fnd 1번째 자리에 분할한 자릿수 표시
        PORTF = 0b1110000;
        PORTB = seg_part[n1000];
        delay_us(500);
        PORTF = 0xf0;
    }
    
}

// 인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드 실행
interrupt [EXT_INT1] void external_int1(void)
{   
    // nomal mode, 클럭 사용X
    TCCR0 = 0x00;
    // catch에 1 저장
    catch = 1;
}

interrupt [TIM0_OVF] void timer_int0(void)
{
    // Timer0의 TCNT 시작값 139로 설정
    TCNT0 = 139;
    // distance 값을 1씩 증가
    distance++;
}