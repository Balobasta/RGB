#include <stm32f10x_conf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RGB.h"


void init_rgb(GPIO_InitTypeDef *GPIOx, uint16_t GPIO_Pin, TIM_TypeDef *TIMx,int channel,int intensity,int arr){
	TIM_OCInitTypeDef  TIM_OCInitStruct;
	GPIO_InitTypeDef  gpio;
	TIM_TimeBaseInitTypeDef Timer;

	gpio.GPIO_Pin =GPIO_Pin;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&gpio);

    TIM_TimeBaseStructInit(&Timer);
	Timer.TIM_CounterMode = TIM_CounterMode_Up;
	Timer.TIM_Prescaler =(SystemCoreClock/1000000)-1;
	Timer.TIM_Period = arr;
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
void set_pwm(TIM_TypeDef *TIMx,int channel,uint8_t colour){
	   switch(channel){
	    case 1 :{
	    	 TIMx->CCR1 = colour*(TIMx->ARR - 1)/255;
	    	 break;
	    }
	    case 2: {
	    	TIMx->CCR2 = colour*(TIMx->ARR - 1)/255;
			break;
	    }
	    case 3:{
	    	TIMx->CCR3 = colour*(TIMx->ARR - 1)/255;
		    break;
	    }
	    case 4: {
	    	TIMx->CCR4 = colour*(TIMx->ARR - 1)/255;
		    break;
	    }
	           }
}

void set_rgb(uint8_t red, uint8_t green,uint8_t blue){
	set_pwm(PWM_LED_TIMER,PWM_LED_CHANEL_RED,red);
	set_pwm(PWM_LED_TIMER,PWM_LED_CHANEL_GREEN,green);
	set_pwm(PWM_LED_TIMER,PWM_LED_CHANEL_BLUE,blue);

}
uint8_t get_rgb_red(){
	return  ((PWM_LED_TIMER->CCR3)*255/(PWM_LED_TIMER->ARR-1));
}
uint8_t get_rgb_green(){
    return  ((PWM_LED_TIMER->CCR2)*255/(PWM_LED_TIMER->ARR-1));
}
uint8_t get_rgb_blue(){
	return  ((PWM_LED_TIMER->CCR4)*255/(PWM_LED_TIMER->ARR-1));
}
