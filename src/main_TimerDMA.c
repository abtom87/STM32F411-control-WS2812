/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "dma_timer.h"
#include "gpio_led.h"
#include "stm32f4xx.h"
#include "timer_drv.h"
#include "usart2_comm.h"

volatile unsigned long msTicks = 0;
void                   Delay_ms(unsigned long del_count) {
     del_count *= 1000;
     msTicks = del_count;
     while (msTicks != 0)
          ;
}
void SysTick_Init(void) {
     /****************************************
      *SystemFrequency/1000      1ms         *
      *SystemFrequency/100000    10us        *
      *SystemFrequency/1000000   1us         *
      *****************************************/

     // SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
     while (SysTick_Config(SystemCoreClock / 1000000) != 0) {
     }
}

int main(void) {
     SystemInit();
     SysTick_Init();

     /*Initialise GPIO and USART for debugging purpose*/
     init_gpio_pins();
     init_USART2();

     /* Initialise DMA for Timer*/
     init_dma_timer();
     enable_dma_timer_irq();

     /*Initialise timer and the PIN where Output waveform will be
      * measured*/
     init_timer();
     enable_alt_func_gpio();

     while (1)
          ;
}

void SysTick_Handler() {}

volatile uint32_t dutycycle_buffer[BUFF_SIZE];
void              DMA1_Stream7_IRQHandler(void) {
     // GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
     if (DMA_GetITStatus(DMA1_Stream7, DMA_IT_TCIF7) != RESET) {
          GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
          dutycycle_buffer[0]  = 10;
          dutycycle_buffer[1]  = 20;
          dutycycle_buffer[2]  = 30;
          dutycycle_buffer[3]  = 40;
          dutycycle_buffer[4]  = 50;
          dutycycle_buffer[5]  = 60;
          dutycycle_buffer[6]  = 70;
          dutycycle_buffer[7]  = 80;
          dutycycle_buffer[8]  = 90;
          dutycycle_buffer[9]  = 100;
          dutycycle_buffer[10] = 90;
          dutycycle_buffer[11] = 80;
          DMA_ClearITPendingBit(DMA1_Stream7, DMA_IT_TCIF7);
     }
}
