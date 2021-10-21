/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

extern double ticksKey1Pressed;
extern double ticksKey2Pressed;
extern uint32_t lastTimeTicksButtonsPressed;

extern uint8_t leftButtonShortPressCounter;
extern uint8_t leftButtonLongPressCounter;
extern uint8_t leftButtonLongLongPressCounter;
extern uint8_t rightButtonShortPressCounter;
extern uint8_t rightButtonLongPressCounter;
extern uint8_t rightButtonLongLongPressCounter;
extern uint8_t bothButtonsPressCounter;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim3;

/* USER CODE BEGIN EV */


double ticksButton0Pressed;
double ticksButton1Pressed ;



/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	GPIO_PinState pinState = HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
	if (pinState == GPIO_PIN_SET)
	{
		//ticksButton0Pressed = HAL_GetTick();
		ticksButton0Pressed = xTaskGetTickCount();
		lastTimeTicksButtonsPressed = ticksButton0Pressed; 
	}
	if (pinState == GPIO_PIN_RESET)
	{
		if (ticksButton0Pressed > 0)
		{
			//double ticksPeriodButtonPressed = HAL_GetTick() - ticksButton1Pressed;
			double ticksPeriodButtonPressed = xTaskGetTickCount() - ticksButton0Pressed;
			
			ticksButton0Pressed = 0;
			if (ticksPeriodButtonPressed > 0 & ticksPeriodButtonPressed < FIRST_PRESSING_EDGE_MS & SETUP_MODE == 1)
			{
				rightButtonShortPressCounter += 1;
			}
			if (ticksPeriodButtonPressed >= FIRST_PRESSING_EDGE_MS & ticksPeriodButtonPressed < SECOND_PRESSING_EDGE_MS & SETUP_MODE == 1)
			{
				rightButtonLongPressCounter += 1;
			}
			if (ticksPeriodButtonPressed >= SECOND_PRESSING_EDGE_MS & SETUP_MODE == 1)
			{
				rightButtonLongLongPressCounter += 1;
			}	
			if (ticksPeriodButtonPressed > 0 & ticksButton1Pressed > 0)
			{
				bothButtonsPressCounter += 1;
			}
		}
	}	
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */
	GPIO_PinState pinState = HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
	if (pinState == GPIO_PIN_SET)
	{
		//ticksButton1Pressed = HAL_GetTick();
		ticksButton1Pressed = xTaskGetTickCount();
		lastTimeTicksButtonsPressed = ticksButton1Pressed; 
	}
	
	if (pinState == GPIO_PIN_RESET)
	{
		if (ticksButton1Pressed > 0)
		{
			//double ticksPeriodButtonPressed = HAL_GetTick() - ticksButton0Pressed;
			double ticksPeriodButtonPressed = xTaskGetTickCount() - ticksButton1Pressed;
			
			ticksButton1Pressed = 0;
			if (ticksPeriodButtonPressed > 0 & ticksPeriodButtonPressed < FIRST_PRESSING_EDGE_MS & SETUP_MODE == 1)
			{
				leftButtonShortPressCounter += 1;
			}
			if (ticksPeriodButtonPressed >= FIRST_PRESSING_EDGE_MS & ticksPeriodButtonPressed < SECOND_PRESSING_EDGE_MS & SETUP_MODE == 1)
			{
				leftButtonLongPressCounter += 1;
			}
			if (ticksPeriodButtonPressed >= SECOND_PRESSING_EDGE_MS & SETUP_MODE == 1)
			{
				leftButtonLongLongPressCounter += 1;
			}	
			if (ticksPeriodButtonPressed > 0 & ticksButton0Pressed > 0)
			{
				bothButtonsPressCounter += 1;
			}
		}
	}		
	
	
  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
