#include <mega128.h>
#include <Delay.h>

// fnd 세그먼트 파트 표시 배열(0~9)
char seg_part[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void main(void)
{
    // fnd 사용을 위한 출력 선언
    // PORTB: fnd 표시를 위한 7-segment led
    // PORTF: fnd 표시를 위한 7-segment 자릿수
    DDRB = 0xff;
    DDRF = 0xf0;
    // PORTE 전부 입력으로 설정
    DDRE = 0x00;

    // PORTF에 연결된 fnd 마지막 자리 on
    PORTF = 0xe0;

    // 전역 인터럽트 허용
    SREG = 0x80;
    // 인터럽트 4~7번 하강에지 사용
    EICRB = 0xaa;
    // 지역 인터럽트 4~7번 사용
    EIMSK = 0xf0;

    // 인터럽트를 대기하는 동안 fnd에 0 표시
    while (1) PORTB = 0x3f;
}

// 인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드 실행
interrupt [EXT_INT4] void ext_int4(void)
{
    // fnd 4번째 자리 on
    PORTF = 0xe0;
    // fnd 4번째 자리에 4 표시
    PORTB = seg_part[4];
}

interrupt [EXT_INT5] void ext_int5(void)
{
    // fnd 3번째 자리 on
    PORTF = 0xd0;
    // fnd 3번째 자리에 5 표시
    PORTB = seg_part[5];
}

interrupt [EXT_INT6] void ext_int6(void)
{
    // fnd 2번째 자리 on
    PORTF = 0xb0;
    // fnd 2번째 자리에 6 표시
    PORTB = seg_part[6];
}

interrupt [EXT_INT7] void ext_int7(void)
{
    // fnd 1번째 자리 on
    PORTF = 0x70;
    // fnd 1번째 자리에 7 표시
    PORTB = seg_part[7];
}