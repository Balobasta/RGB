#include <stm32f10x_conf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RGB.h"
uint8_t red1=128,green1=128,blue1=128;
#define hight 256
#define midle 128
#define low 20
#define PWM_LED_TIMER TIM3
#define PWM_LED_CHANEL_GREEN 2
#define PWM_LED_CHANEL_RED 3
#define PWM_LED_CHANEL_BLUE 4
#define PIN_RED GPIO_Pin_0
#define PIN_GREEN GPIO_Pin_7
#define PIN_BLUE GPIO_Pin_1
#define GPIO_RED GPIOB
#define GPIO_GREEN GPIOA
#define GPIO_BLUE GPIOB
TIM_OCInitTypeDef  TIM_OCInitStruct;
GPIO_InitTypeDef  gpio;
TIM_TimeBaseInitTypeDef Timer;
void Init_RGB(GPIO_InitTypeDef *GPIOx, uint16_t GPIO_Pin, TIM_TypeDef *TIMx,int channel,int intensity){
	gpio.GPIO_Pin =GPIO_Pin;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&gpio);

    TIM_TimeBaseStructInit(&Timer);
	Timer.TIM_CounterMode = TIM_CounterMode_Up;
	Timer.TIM_Prescaler =(SystemCoreClock/1000000)-1;
	Timer.TIM_Period = 100;
	TIM_TimeBaseInit(TIMx, &Timer);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = intensity;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    switch(channel){
    case 1 :{
    	 TIM_OC1Init(TIMx,&TIM_OCInitStruct);
    	 TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
    	 break;
    }
    case 2: {
    	TIM_OC2Init(TIMx,&TIM_OCInitStruct);
    	TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
    	break;
    }
    case 3:{
    	TIM_OC3Init(TIMx,&TIM_OCInitStruct);
		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
		break;
    }
    case 4: {
    	TIM_OC4Init(TIMx,&TIM_OCInitStruct);
		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
		break;
    }
    }
    TIM_Cmd(TIMx,ENABLE);
}

void SET_RGB(uint8_t red, uint8_t green,uint8_t blue){
	Init_RGB(GPIO_RED,PIN_RED,PWM_LED_TIMER,PWM_LED_CHANEL_RED,red);
	Init_RGB(GPIO_BLUE,PIN_BLUE,PWM_LED_TIMER,PWM_LED_CHANEL_BLUE,blue);
	Init_RGB(GPIO_GREEN,PIN_GREEN,PWM_LED_TIMER,PWM_LED_CHANEL_GREEN,green);
    red1=red;
    green1=green;
    blue1=blue;
}
uint8_t GET_RGB_RED(){
          return red1;
}
uint8_t GET_RGB_GREEN(){
	   return green1;
}
uint8_t GET_RGB_BLUE(){
	   return blue1;
}
