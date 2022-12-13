#include <mega128.h>
#include <delay.h>
#include <stdio.h>

// LCD 사용을 위한 어샘블러 LCD 포트 선언
#asm
    .equ_lcd_port = 0x12;
#endasm

#include <lcd.h>

// 문자열 저장을 위한 변수 배열 선언
char string[30];

// 차동 AD Converter의 값 표기 함수 먼저 선언
void diff_ad_display(int);

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
    // AD Converter 7~6bit: 외부 전원 사용, 5bit: 변환 결과값 LSB를 맞추어 저장, 4~0bit: 10000--> +ADC0/-ADC1의 차동 입력, gain: 1
    ADMUX = 0x10;
    // AD Converter 7bit: 동작 허용, 6bit: 변환X, 5bit: 단일 변환 모드, 3bit: 인터럽트 비허용, 2~0bit: 분주비 128
    ADCSRA = 0x87;
    delay_ms(5);

    // LCD 초기화
    lcd_init(16);

    while (1)
    {
        // AD Converter 7bit: 동작 허용, 6bit: 변환O, 5bit: 단일 변환 모드, 3bit: 인터럽트 비허용, 2~0bit: 분주비 128
        ADCSRA = 0xc7;
        // 4bit: 컨버전이 끝나면 1
        // 4bit를 확인하여 컨버전이 끝났는지를 확인
        while ((ADCSRA = 0x01) == 0);

        // 컨버전이 끝났을 경우 ADCH를 8bit shift하고, ADCL과 함게 ad_val에 저장
        ad_val = (int) ADCL + ((int)ADCH << 8);
        // 변환값 표시
        diff_ad_display(ad_val);
    }
    
}

// 차동 변환 값 표시 함수
void diff_ad_display(int val);
{
    // 필요한 변수 정의
    float fval;
    int ival, buf;
    char n100, n10, n1, flag = 0;
    // 기본 부호를 +로 저장
    char sign = "+"

    // 아날로그 입력값이 512 이상의 경우
    if (val > 512)
    {
        // 아날로그 값을 1024에서 빼서 2의 보수를 표현
        fval = (float)(1024 - val);
        // 부호를 음수로 판단
        flag = 1;
        sign = "-"
    }
    // 아날로그 입력값이 512 이하의 경우
    else fval = (float)val;

    // 아날로그 값을 512(분해능)로 나누어 최대 5의 값으로 만든다
    fval = fval * 5.0 / 512.0;
    // 소수점 3째 자리에서 반올림
    ival = (int)(fval * 100.0 + 0.5);

    // 정수부 자리 추출
    n100 = ival / 100;
    buf = ival % 100;

    // 소수점 첫째 자리 추출
    n10 = buf / 10;
    // 소수점 둘째 자리 추출
    n1 = buf % 10;

    // sprintf(변수," ") " "의 값을 변수에 대입
    // %c%d.%d%d, sign, n100, n10, n1 %자리에 뒤의 변수 값을 순서대로 대입
    sprintf(string, "A/D C Voltage is %c%d.%d%dV", sign, n100, n10, n1);
    // lcd 커서 첫째 줄 첫번째 자리로 이동
    lcd_gotoxy(0, 0);
    delay_ms(100);
    // lcd의 커서 자리에서 부터 표시
    lcd_puts(string);
}