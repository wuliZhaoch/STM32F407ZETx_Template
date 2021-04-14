/*
 * system.h
 *
 *  Created on: 2021.3.29
 *      Author: Wulizhaoch
 *
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "common.h"


void RCC_CLK_Enable(void);

void SystemClock_Config(void);

void Error_Handler(void);

void System_GetChipID(void);


#endif /* SYSTEM_H_ */
