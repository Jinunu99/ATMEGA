#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// 사용할 포트를 정의하는 부분
#define FND_DDR			 DDRA
#define FND_PORT		 PORTA
#define PWM_DDR			 DDRB
#define FND_SELECT_DDR   DDRB
#define FND_SELECT_PORT  PORTB
#define FND_DATA_DDR     DDRC
#define FND_DATA_PORT    PORTC
#define LED_DDR			 DDRD
#define LED_PORT		 PORTD
#define BUTTON_DDR		 DDRG
#define BUTTON_PORT		 PORTG


// 7세그먼트의 0 ~ 9까지 제어값을 배열에 저장
uint8_t FND_Number[] = 
{ 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67 };

//uint8_t LED_Number[] =
//{ 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };

uint8_t count = 10;
volatile uint8_t ms_count = 0;
uint8_t flag = 0;     // fndDisplay를 출력할지 결정하는 flag

ISR(TIMER0_OVF_vect) // 타이머/카운터 오버플로우 인터럽트 벡터
{
	// 주기 16us를 256번 카운팅되면 => 4ms마다 인터럽트 발생됨
	// 4ms를 200번 카운트하면 1초가 됨
	ms_count++; // 4ms마다 카운트 됨
	if(ms_count == 250) // ms_count가 250이 되면 실제로 1초가 되었다는 뜻
	{
		ms_count = 0;
		count--;
	}
}

void fndDisplay(uint8_t data)
{
	// static을 통해 프로그램이 완전 종료될 때까지 fndDisplay 함수가 끝나고 어떤 값을 기다릴 꺼임
	// static으로 선언했기 때문에 프로그램이 실행될때만 한번 0으로 초기화 됨
	static uint8_t position = 0; // digit를 선택하는 포지션
	uint8_t fndData[10] =
	{ 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67 };
	
	switch(position)
	{
		case 0:
		// 첫번째 자리의 FND를 표시하기 위해서 0번핀 LOW / 1, 2, 3번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 0);	// digit 1번 LED ON
		FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<3); // digit 2, 3, 4번 LED OFF
		FND_DATA_PORT = fndData[data/1000]; // 천의 자리를 구하기 위해 1000으로 나눔
		break;
		
		case 1:
		// 두번째 자리의 FND를 표시하기 위해서 1번핀 LOW / 0, 2, 3번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 1);	// digit 2번 LED ON
		FND_SELECT_PORT |= (1<<0) | (1<<2) | (1<<3); // digit 1, 3, 4번 LED OFF
		FND_DATA_PORT = fndData[data/100%10]; // 백의 자리 구하기
		break;
		
		case 2:
		// 세번째 자리의 FND를 표시하기 위해서 2번핀 LOW / 0, 1, 3번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 2);	// digit 3번 LED ON
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<3); // digit 1, 2, 4번 LED OFF
		FND_DATA_PORT = fndData[data/10%10]; // 십의 자리 구하기
		break;
		
		case 3:
		// 네번째 자리의 FND를 표시하기 위해서 3번핀 LOW / 0, 1, 2번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 3);	// digit 4번 LED ON
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<2); // digit 1, 2, 3번 LED OFF
		FND_DATA_PORT = fndData[data%10]; // 일의 자리 구하기
		break;
	}
	position++;				 // 다음 자릿수로 이동하기 위해 ++ 해줌
	position = position % 4; // 4자리 출력 후엔 다시 첫번째로 가라
}

int main(void)
{
    FND_DDR = 0xff;        // fnd를 출력으로
    FND_SELECT_DDR = 0x0f; // 선택핀 0000 1111로 설정
    FND_DATA_DDR = 0xff;   // 데이터핀 설정
    LED_DDR = 0xff;        // led를 출력으로
    LED_PORT = 0x00;       // led를 꺼진 상태로 초기화
    BUTTON_DDR = 0x00;     // button을 입력으로
    uint8_t buttonData;    // button의 정보를 저장하는 변수
   
    PWM_DDR |= (1 << DDRB4); // OC0을 사용하기 위해 PB4번 핀 이용
    // 레지스터 초기화 (pwm 사용을 위함)
    TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS02) | (1 << CS01);
    OCR0 = 0; // OCR0값을 조절해서 pwm 제어
    
	sei(); // 글로벌 인터럽트 활성화
	TIMSK = (1 << TOIE0); // 오버플로우 인터럽트 활성화 (타이머를 구현하기 위해)
	
    while (1) 
    {
      buttonData = PING;
      if((buttonData & (1 << 4)) == 0) // 4번 버튼 클릭
      {
         FND_PORT = FND_Number[0]; // 정지
         OCR0 = 255 * 0; // pwm 0%
		 flag = 0;
      }
      else if((buttonData & (1 << 3)) == 0) // 3번 버튼
      {
         FND_PORT = FND_Number[1]; // 1단
         OCR0 = 255 / 2; // pwm 50%
         flag = 0;
      }
      else if((buttonData & (1 << 2)) == 0) // 2번 버튼
      {
         FND_PORT = FND_Number[2]; // 2단
         OCR0 = 255 * 9 / 10; // pwm 90%
		 flag = 0;
      }
      else if((buttonData & (1 << 1)) == 0) // 1번 버튼
      {
         flag = 1;
		 count = 10;   // 카운트는 10초부터 시작
		 ms_count = 0;
      }
	  
	  if(flag == 1) // 1번 버튼을 눌렀다면
	  {
		  fndDisplay(count); // count 숫자 출력
		  if(count == 0)
		  {
			  flag = 0;
			  FND_PORT = FND_Number[0]; // 정지
			  OCR0 = 255 * 0; // pwm 0%
		  }
	  }
	  else
	  {
		  FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<2) | (1<<3); // FND_4개 OFF
	  }
      _delay_ms(1);
    }
}