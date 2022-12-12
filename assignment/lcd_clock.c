#include <mega128.h>        
#include <delay.h>
#include <stdio.h>

#define FUNCSET		0x28	// Function Set
#define ENTMODE		0x06	// Entry Mode Set
#define ALLCLR		0x01	// All Clear
#define DISPON		0x0c 	// Display On    
#define LINE2		0xC0	// 2nd Line Move    
#define HOME		0x02	// Cursor Home     
#define CURON 		0x0F	// Cursor On                   

typedef unsigned char BYTE;
int hour=12, min=0, sec=0; 
BYTE tog=0,set=0;           
void LCD_init(void);
void LCD_String(char *);
void Busy(void);
void Command(unsigned char);
void Data(unsigned char);
void Timer_Interrupt_Initialize(void);
void External_Interrupt_Initialize(void);
void Time_Display(void);
void Count_up(void);

void main(void)
{                          
	
	DDRB = 0xFF;	// OC1C(PB7) 방향설정
	LCD_init();       
   	// 첫 번째 라인에 출력
    LCD_String("   Jeong InHo   ");
	Timer_Interrupt_Initialize();            
	External_Interrupt_Initialize();
	Time_Display();
	#asm ("sei")		// 전역 인터럽트 플래그 셋.
	while(1);		// 무한 루프		
}

// LCD 초기화  
void LCD_init(void)
{       
	DDRD = 0xff;			// 포트 D 출력 설정
	PORTD &= 0xfb;		// E = 0;
	delay_ms(15);
	Command(0x20);
	delay_ms(5);
	Command(0x20);
	delay_us(100);
	Command(0x20);
	Command(FUNCSET);
	Command(DISPON);
	Command(ALLCLR);
	Command(ENTMODE);
}

// 문자열 출력 함수
void LCD_String(char flash *str)
{
	char flash  *pStr=0;
	pStr = str;	
	while(*pStr)  Data(*pStr++);
}	  

// 인스트럭션 쓰기 함수
void Command(unsigned char byte)
{
	Busy();

	// 인스트럭션 상위 바이트
	PORTD = (byte & 0xf0);		// 데이터	
	PORTD &= 0xfe;		//RS = 0;           
	PORTD &= 0xfd;		//RW = 0;  
	delay_us(1);     
	PORTD |= 0x04;		// E = 1;
	delay_us(1);
	PORTD &= 0xfb;		// E = 0;

	// 인스트럭션 하위 바이트
   PORTD = ((byte<<4) & 0xf0);	// 데이터
	PORTD &= 0xfe;		// RS = 0;
	PORTD &= 0xfd;		// RW = 0;
	delay_us(1);     	
	PORTD |= 0x04;		// E = 1;
	delay_us(1);
	PORTD &= 0xfb;		// E = 0;
}

//데이터 쓰기 함수
void Data(unsigned char byte)
{
	Busy();
   	// 데이터 상위 바이트
	PORTD = (byte & 0xf0);		// 데이터
	PORTD |= 0x01;		// RS = 1;
	PORTD &= 0xfd;		// RW = 0;
	delay_us(1);     	
	PORTD |= 0x04;		// E = 1;
	delay_us(1);
	PORTD &= 0xfb;		// E = 0;

	// 데이터 하위 바이트
	PORTD = ((byte<<4) & 0xf0);  	// 데이터
	PORTD |= 0x01;		// RS = 1;
	PORTD &= 0xfd;		// RW = 0;     
	delay_us(1);     	
	PORTD |= 0x04;		// E = 1;
	delay_us(1);
	PORTD &= 0xfb;		// E = 0;
}

// Busy Flag Check -> 일반적인 BF를 체크하는 것이 아니라
// 일정한 시간 지연을 이용한다.
void Busy(void)
{
	delay_ms(2);
}

// 타이머 인터럽트 비교 매치 인터럽트 초기화 함수                
void Timer_Interrupt_Initialize(void)
{                     
	// 타이머/카운터 인터럽트 초기화
	ETIMSK = 0x01;	// OCIE1C = '1'               
	TCCR1A = 0x04;	// COM1Cx = '01' : OC1C 토글
	TCCR1B = 0x05;	// 프리스케일 = CK/1024
	TCNT1 = 0x0000;	// 타이머/카운터1 레지스터 초기값 : 16 비트 
// 타이머/카운터1 비교 매치 B 레지스터 : 16 비트
	OCR1CH = (7812 & 0xFF00) >> 8;
	OCR1CL = 7812 & 0x0FF;
}

// 외부 인터럽트 요구 초기화 함수                                       
void External_Interrupt_Initialize(void)
{
	// 외부 인터럽트 초기화           
	EICRB = 0b00001010;	// 외부 인터럽트 4, 5 : 하강 에지 
	EIMSK = 0b00110000;	// 외부 인터럽트 4,5 인에이블'
}

// LCD에 시간을 표시하는 함수                
void Time_Display(void)
{
	char Time_buf[16];
	sprintf(Time_buf,"  [%02u : %02u : %02u]  ",hour, min, sec);         
	Command(LINE2);
	LCD_String(Time_buf);     
}

// 시간 증가 함수
void Count_up(void)
{
	if(sec != 59) sec++;  		// sec count-up
	else{
		sec = 0;
		if(min != 59) min++;		// min count-up
		else{
			min = 0;
			if(hour != 12) hour++;	// hour count-up
			else hour = 1;
		}
	}        
	Time_Display();	// 시간 표시
}

// 타이머/카운터 1 비교 B 매치 인터럽트 서비스 루틴 
// 0.5초마다 인터럽트 발생 
interrupt [TIM1_COMPC] void timer1_compc(void) 
{           
	TCNT1 = 0x0000; 	// 타이머/카운터 1 레지스터 초기화                  
	// 1초 마다 한번씩 카운트한다. 
	if(tog == 0) tog++;	
	else {
		tog = 0;
		if(set == 0) Count_up();  
	}                                  
	// 시간 조정 모드에서의 커서 위치 설정
	if(set == 1) Command(0x88);	// min의 위치
	else if(set == 2) Command(0x83);	// hour의 위치
}

// 외부 인터럽트 요구 4 서비스 루틴     
// 시간 설정 자리수 이동
interrupt [EXT_INT4] void external_int4(void)
{                           
	Command(CURON);  	// 커서 표시
	if (set != 2) set++;	// 자릿수 이동
	else set = 0;     	// set=0(표시모드), set=1(분조정), set=2(시간조정)
}

// 외부 인터럽트 요구 5 서비스 루틴
// 분과 시를 증가한다. 
interrupt [EXT_INT5] void external_int5(void)
{                      
	if(set == 1){         	// min count-up
		if(min != 59) min++;
		else min = 0;
	}
	else if(set == 2){    	// hour count-up
		if(hour != 12) hour++;
		else hour = 1;
	}                  
	Time_Display();		// 시간 표시
}