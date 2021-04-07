/*
 * chip_id.c
 *
 *  Created on: 2020-04-02
 *      Author: wuliZhao_ch
 *       brief: Read Chip Unique ID (96-bit)
 */
#include "chip_id.h"


void GET_ChipID(ChipIDTypeDef *CHIPID)
{
    CHIPID->Chip_ID_H = HAL_GetUIDw0();
    CHIPID->Chip_ID_M = HAL_GetUIDw1();
    CHIPID->Chip_ID_L = HAL_GetUIDw2();
}
