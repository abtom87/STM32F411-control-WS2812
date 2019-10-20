/*
 * timer_drv.h
 *
 *  Created on: May 15, 2018
 *      Author: abel
 */

#ifndef TIMER_DRV_H_
#define TIMER_DRV_H_

#define ARR_VALUE 125U
#define PSC_VAL 0U
#define DUTY_CYCLE 5U

#include "stm32f4xx_tim.h"

void init_timer(void);

void enable_alt_func_gpio(void);

#endif /* TIMER_DRV_H_ */
