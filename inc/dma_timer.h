/*
 * dma_timer.h
 *
 *  Created on: Oct 19, 2019
 *      Author: abel
 */

#ifndef DMA_TIMER_H_
#define DMA_TIMER_H_

#include "stm32f4xx_dma.h"

void init_dma_timer(void);
void enable_dma_timer_irq(void);

#define BUFF_SIZE 12U
extern volatile uint32_t dutycycle_buffer[BUFF_SIZE];

#endif /* DMA_TIMER_H_ */
