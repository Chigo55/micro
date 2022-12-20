#include <mega128.h>
#include <Delay.h>

// fnd 세그먼트 파트 표시 배열(4~7)
char seg_part[4] = {0x66, 0x6d, 0x7d, 0x07};

void main(void)
{
    // PORTE 전부 입력으로 설정
    DDRE = 0x00;
    // PORTB 전부 출력으로 설정
    DDRB = 0xff;
    // PORTF 상위 4bit 출력으로 설정
    DDRF = 0xf0;

    // PORTF에 연결된 fnd 마지막 자리 on
    PORTF = 0xe0;
    // fnd에 0표시
    PORTB = 0x3f;

    // 전역 인터럽트 허용
    SREG = 0x80;
    // 인터럽트 4~7번 하강에지 사용
    EICRB = 0xaa;
    // 지역 인터럽트 4~7번 사용
    EIMSK = 0xf0;

    // 인터럽트 대기
    while (1);
}

//인터럽트 서비스 루틴: 인터럽트가 들어오면 아래의 코드 실행
interrupt [EXT_INT4] void ext_int4(void)
{   
    // fnd에 4 표시
    PORTB = seg_part[0];
}

interrupt [EXT_INT5] void ext_int5(void)
{
    // fnd에 5 표시
    PORTB = seg_part[1];
}

interrupt [EXT_INT6] void ext_int6(void)
{
    // fnd에 6 표시
    PORTB = seg_part[2];
}

interrupt [EXT_INT7] void ext_int7(void)
{
    // fnd에 7 표시
    PORTB = seg_part[3];
}