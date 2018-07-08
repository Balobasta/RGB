#include <stm32f10x_conf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <RGB.h>


#define rb_size 9
uint8_t rb[rb_size],data;
int led_state=0,rb_index=0,wb_index=0,f=0;

uint16_t get_char(void);

#define isdigit tmp=='0'||tmp=='1'||tmp=='2'||tmp=='3'||tmp=='4'||tmp=='5'||tmp=='6'||tmp=='7'||tmp=='8'||tmp=='9'

TIM_OCInitTypeDef  TIM_OCInitStruct;
GPIO_InitTypeDef  gpio;
TIM_TimeBaseInitTypeDef Timer;


void init_usart(void){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		GPIO_StructInit(&gpio);
		gpio.GPIO_Pin = GPIO_Pin_1;
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&gpio);


		//TX USART
		gpio.GPIO_Mode = GPIO_Mode_AF_PP;
		gpio.GPIO_Pin = GPIO_Pin_9;
		GPIO_Init(GPIOA,&gpio);

		//RX USART
		gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		gpio.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOA,&gpio);

		USART_InitTypeDef us;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

		us.USART_BaudRate = 9600;
		us.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		us.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		us.USART_Parity = USART_Parity_No;
		us.USART_StopBits = USART_StopBits_1;
		us.USART_WordLength = USART_WordLength_8b;
		USART_Init(USART1,&us);

		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART1,ENABLE);

		NVIC_EnableIRQ(USART1_IRQn);

}

void usart_char(uint16_t x){
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, x);
}

void usart_string(char *str){
	  int i;
	  for(i=0; i<=strlen(str);i++)
		  usart_char(str[i]);
  }

void USART1_IRQHandler(void) {
  	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
  		      	if ((USART1->SR & (USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE|USART_FLAG_ORE)) == 0) {
  						rb[wb_index]=(uint8_t)(USART_ReceiveData(USART1)& 0xFF);
  						wb_index=(wb_index+1)%rb_size;
  					}
  					else USART_ReceiveData(USART1);
  		  }
  	}

uint16_t usart_get_char(void)
  {
  	uint16_t data;
  	while (rb_index==wb_index);
  	data = rb[rb_index];
  	rb_index = (rb_index+1)%rb_size;
  	usart_char(data);
  	return data;
  }

void usart_int(unsigned int x){
	char str[20];
	itoa(x, str, 10);
	usart_string(str);
}

void delay_loop(uint32_t DelayTicks) {
__asm__ __volatile__ (
"1: \n"
"sub %[DelayTicks], %[DelayTicks], #1\n" //1tick
"cmp %[DelayTicks], #0 \n" // 1tick
"bne 1b \n" //1 or 2 ticks
: [DelayTicks] "+r"(DelayTicks)
);
}

int main(void)
{
	char *l[100];
	uint8_t red=0,green=0,blue=0;
	uint8_t buf[100]={0},tmp;
	int buf_i=0,f1=0,f2=0,f3=0,g1=0,g2=0,g3=0,k=0;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    init_usart();
    usart_string("\r r red_part g green_part  b blue_part \n\r colour_part - integer number, \n\r example r256 g124 b57 \n ");
    init_rgb(GPIO_RED, PIN_RED, PWM_LED_TIMER,PWM_LED_CHANEL_RED,0);
    init_rgb(GPIO_GREEN, PIN_GREEN, PWM_LED_TIMER,PWM_LED_CHANEL_GREEN,0);
    init_rgb(GPIO_BLUE, PIN_BLUE, PWM_LED_TIMER,PWM_LED_CHANEL_BLUE,0);
    set_rgb(128,0,0);
    delay_loop(SystemCoreClock/25);
    set_rgb(0,128,0);
    delay_loop(SystemCoreClock/25);
    set_rgb(0,0,128);
    delay_loop(SystemCoreClock/25);
    set_rgb(128,128,128);
    red=green=blue=128;
    while(1)
    {
    	tmp=usart_get_char();
    	if (tmp=='r'){
    		g1=1;
    		buf_i=0;
    		tmp=usart_get_char();
    		if (isdigit){
    			f1=1;
    		while(isdigit)
    		{
    			buf[buf_i]=tmp;
    			buf_i++;
    			tmp=usart_get_char();
    		}
    		buf[buf_i]=0;
    		red=(uint8_t)atoi(buf);
    		}
    	}
    	if (tmp=='g'){
    		g2=1;
    		buf_i=0;
    		tmp=usart_get_char();
    		if (isdigit){
    			f2=1;
    		while(isdigit)
    		{
    			buf[buf_i]=tmp;
    			buf_i++;
    			tmp=usart_get_char();
    		}
    		buf[buf_i]=0;
    	    green=(uint8_t)atoi(buf);

    		}else if (tmp=='e'){
    			g2=0;
    			tmp=usart_get_char();
    			if (tmp=='t'){
    				tmp=usart_get_char();
    					if (tmp=='_'){
    						tmp=usart_get_char();
    							if (tmp=='r'){
    								tmp=usart_get_char();
    								if (tmp=='g'){
    									tmp=usart_get_char();
    									if(tmp=='b'){
    										tmp=usart_get_char();
    										k=1;
    									}
    								}
    							}
    		}
    		}
    	} }
    	if (tmp=='b'){
    		g3=1;
    		buf_i=0;
    		tmp=usart_get_char();
    		if (isdigit){
    			f3=1;
    		while(isdigit)
    		{
    			buf[buf_i]=tmp;
    			buf_i++;
    			tmp=usart_get_char();
    		}
    		buf[buf_i]=0;
    		blue=(uint8_t)atoi(buf);
    		}
    	}
    	if (tmp==13) {

    	if (k){

    		f1=f2=f3=g1=g2=g3=0;
    		k=0;
    		usart_string("\n\r r:");
    		itoa( get_rgb_red(),l,10);
    		usart_string (l);
    		usart_string("\t");

    		usart_string(" g:");
			itoa( get_rgb_green(),l,10);
			usart_string (l);
			usart_string("\t");

			usart_string(" b:");
			itoa( get_rgb_blue(),l,10);
			usart_string (l);
			usart_string("\t");

			usart_string("\n\r");
    	}else{
    		if (!f1 && g1) red=0;
    		if (!f2 && g2) green=0;
    		if (!f3 && g3) blue=0;
    		usart_string("\n\r");
    		f1=f2=f3=g1=g2=g3=0;
    		set_rgb(red,green,blue);
    	}
    	}

    }
}
