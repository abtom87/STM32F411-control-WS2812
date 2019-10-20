/*
 * timer_src.c
 *
 *  Created on: May 15, 2018
 *      Author: abel
 */

#include "timer_drv.h"

void enable_alt_func_gpio(void) {
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

     /* PB0 TIM3-CH3 */

     GPIO_InitTypeDef OC_GPIO_Struct;
     OC_GPIO_Struct.GPIO_Mode  = GPIO_Mode_AF;
     OC_GPIO_Struct.GPIO_OType = GPIO_OType_PP;
     OC_GPIO_Struct.GPIO_Pin   = GPIO_Pin_0;
     OC_GPIO_Struct.GPIO_PuPd  = GPIO_PuPd_UP;
     OC_GPIO_Struct.GPIO_Speed = GPIO_Fast_Speed;

     GPIO_Init(GPIOB, &OC_GPIO_Struct);

     GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
}

void init_timer(void) {
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

     TIM_TimeBaseInitTypeDef TimInitStruct;
     TIM_OCInitTypeDef Tim2OCInitStr;

     /*Output Freq = Fclock/ ( (ARR+1)*(Prescaler+1)*(RCR+1) )*/

     TimInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
     TimInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
     TimInitStruct.TIM_Period            = ARR_VALUE;
     TimInitStruct.TIM_Prescaler         = PSC_VAL;
     TimInitStruct.TIM_RepetitionCounter = 0;

     TIM_TimeBaseInit(TIM3, &TimInitStruct);

     Tim2OCInitStr.TIM_Pulse       = (uint32_t)(DUTY_CYCLE * ARR_VALUE / 100);
     Tim2OCInitStr.TIM_OCMode      = TIM_OCMode_PWM2;
     Tim2OCInitStr.TIM_OCPolarity  = TIM_OCPolarity_Low;
     Tim2OCInitStr.TIM_OutputState = TIM_OutputState_Enable;
     TIM_OC3Init(TIM3, &Tim2OCInitStr);
     TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

     // TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);

     TIM_DMAConfig(TIM3, TIM_DMABase_CCR3, TIM_DMABurstLength_8Transfers);

     TIM_Cmd(TIM3, ENABLE);
     TIM_DMACmd(TIM3, TIM_DMA_CC3, ENABLE);
}
