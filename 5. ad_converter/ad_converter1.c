#include <mega128.h>
#include <delay.h>

// fnd 세그먼트 파트 표시 배열(0~9)
char seg_part[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

// AD Converter의 값 표기 함수 먼저 선언
void AD_display(int);

// 메인 함수
void main(void)
{
    // 변환값 변수 선언
    int ad_val;

    // fnd 사용을 위한 출력 선언
    // PORTB: fnd 표시를 위한 7-segment led
    // PORTF: fnd 표시를 위한 7-segment 자릿수
    DDRB = 0xff;
    DDRF = 0xf0;

    // AD Converter 레지스터
    // AD Converter 7~6bit: 외부 전원 사용, 5bit: 변환 결과값 LSB를 맞추어 저장, 4~0bit: 00000--> ADC0 단극성 입력
    ADMUX = 0x00;
    // AD Converter 7bit: 동작 허용, 6bit: 변환X, 5bit: 단일 변환 모드, 3bit: 인터럽트 비허용, 2~0bit: 분주비 128
    ADCSRA = 0x87;
    delay_ms(5);

    while (1)
    {
        // AD Converter 7bit: 동작 허용, 6bit: 변환O, 5bit: 단일 변환 모드, 3bit: 인터럽트 비허용, 2~0bit: 분주비 128
        ADCSRA = 0xc7;
        // 4bit: 컨버전이 끝나면 1
        // 4bit를 확인하여 컨버전이 끝났는지를 확인 
        while ((ADCSRA & 0x10) == 0);
        
        // 컨버전이 끝났을 경우 ADCH를 8bit shift하고, ADCL과 함게 ad_val에 저장
        ad_val = (int)ADCL + ((int)ADCH << 8);
        // 변환값 표시
        AD_display(ad_val);        
    }
    
}

// 변환 값 표시 함수
void AD_display(int val)
{
    // 필요한 변수 정의
    float fval;
    int ival, buf;
    char n100, n10, n1;

    // 아날로그 값을 1024(분해능)로 나누어 최대 5의 값으로 만든다
    fval = (float)val * 5.0 / 1023.0;
    // 소수점 3째 자리에서 반올림
    ival = (int)(fval * 100.0 + 0.5);

    // 정수부 자리 추출
    n100 = ival / 100;
    buf = ival % 100;

    // 소수점 첫째 자리 추출
    n10 = buf / 10;
    // 소수점 둘째 자리 추출
    n1 = buf % 10;

    // 소수점 둘째 자리 표시
    PORTF = 0xe0;
    PORTB = seg_part[n1];
    delay_ms(1);

    // 소수점 첫째 자리 표시
    PORTF = 0xd0;
    PORTB = seg_part[n10];
    delay_ms(1);

    // 정수부 자리 표시
    PORTF = 0xb0;
    PORTB = seg_part[n100];
    delay_ms(1);
}