#ifndef RGB_H
#define RGB_H

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
void init_rgb(GPIO_InitTypeDef *GPIOx, uint16_t GPIO_Pin, TIM_TypeDef *TIMx,int channel,int intensity,int arr);
void set_rgb(uint8_t red, uint8_t green,uint8_t blue);
uint8_t get_rgb_red();
uint8_t get_rgb_green();
uint8_t get_rgb_blue();

#endif
