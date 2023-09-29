/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* TIM10 init function */
void MX_TIM10_Init(void)
{
    /* USER CODE BEGIN TIM10_Init 0 */

    /* USER CODE END TIM10_Init 0 */

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM10);

    /* USER CODE BEGIN TIM10_Init 1 */

    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    /* USER CODE END TIM10_Init 1 */
    LL_TIM_InitTypeDef TIM_InitStruct = {
        .Prescaler = 2 - 1,
        .CounterMode = LL_TIM_COUNTERMODE_UP,
        .Autoreload = 42000 - 1,
        .ClockDivision = LL_TIM_CLOCKDIVISION_DIV1,
    };
    LL_TIM_Init(TIM10, &TIM_InitStruct);
    LL_TIM_EnableARRPreload(TIM10);
    LL_TIM_EnableIT_UPDATE(TIM10);
    /* USER CODE BEGIN TIM10_Init 2 */

    /* USER CODE END TIM10_Init 2 */
}

void MX_TIM11_Init(void)
{
    /* USER CODE BEGIN TIM11_Init 0 */

    /* USER CODE END TIM11_Init 0 */

    /* Peripheral clock enable */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM11);

    /* USER CODE BEGIN TIM11_Init 1 */

    NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);

    /* USER CODE END TIM11_Init 1 */
    LL_TIM_InitTypeDef TIM_InitStruct = {
        .Prescaler = 84 - 1,
        .CounterMode = LL_TIM_COUNTERMODE_UP,
        .Autoreload = 400 - 1,
        .ClockDivision = LL_TIM_CLOCKDIVISION_DIV1,
    };
    LL_TIM_Init(TIM11, &TIM_InitStruct);
    LL_TIM_EnableARRPreload(TIM11);
    LL_TIM_EnableIT_UPDATE(TIM11);
    /* USER CODE BEGIN TIM10_Init 2 */

    /* USER CODE END TIM10_Init 2 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
