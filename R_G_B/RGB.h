#ifndef RGB_H
#define RGB_H

void Init_RGB(GPIO_InitTypeDef *GPIOx, uint16_t GPIO_Pin, TIM_TypeDef *TIMx,int channel,int intensity);
void SET_RGB(uint8_t red, uint8_t green,uint8_t blue);
uint8_t GET_RGB_RED();
uint8_t GET_RGB_GREEN();
uint8_t GET_RGB_BLUE();

#endif
