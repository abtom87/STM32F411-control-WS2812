/*
 * dma_timer.c
 *
 *  Created on: Oct 19, 2019
 *      Author: abel
 */

#include "dma_timer.h"

void init_dma_timer(void) {
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

     // memset(dutycycle_buffer,50,sizeof(uint32_t)*BUFF_SIZE);
     DMA_InitTypeDef DMA_Tmr_InitStruct;
     DMA_StructInit(&DMA_Tmr_InitStruct);
     DMA_Tmr_InitStruct.DMA_BufferSize         = BUFF_SIZE;
     DMA_Tmr_InitStruct.DMA_Channel            = DMA_Channel_5;
     DMA_Tmr_InitStruct.DMA_DIR                = DMA_DIR_MemoryToPeripheral;
     DMA_Tmr_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
     DMA_Tmr_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;
     DMA_Tmr_InitStruct.DMA_Memory0BaseAddr    = (volatile uint32_t) & dutycycle_buffer[0];
     DMA_Tmr_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;
     DMA_Tmr_InitStruct.DMA_Mode               = DMA_Mode_Circular;
     DMA_Tmr_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&TIM3->CCR3;
     DMA_Tmr_InitStruct.DMA_Priority           = DMA_Priority_High;
     DMA_Tmr_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
     DMA_Init(DMA1_Stream7, &DMA_Tmr_InitStruct);

     DMA_ClearITPendingBit(DMA1_Stream7, DMA_IT_TCIF7);
     DMA_ITConfig(DMA1_Stream7, DMA_IT_TC, ENABLE);
     // DMA_ITConfig(DMA1_Stream7, DMA_IT_HT, ENABLE);

     DMA_Cmd(DMA1_Stream7, ENABLE);
}

void enable_dma_timer_irq(void) {
     NVIC_InitTypeDef DMA_NVICStruct;
     DMA_NVICStruct.NVIC_IRQChannel                   = DMA1_Stream7_IRQn;
     DMA_NVICStruct.NVIC_IRQChannelCmd                = ENABLE;
     DMA_NVICStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
     DMA_NVICStruct.NVIC_IRQChannelSubPriority        = 0x00;

     NVIC_Init(&DMA_NVICStruct);
}
