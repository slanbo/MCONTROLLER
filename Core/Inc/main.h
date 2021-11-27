/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
	
	
	
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TERMISTOR_2_Pin GPIO_PIN_0
#define TERMISTOR_2_GPIO_Port GPIOA
#define LIGHT_SENSOR_Pin GPIO_PIN_1
#define LIGHT_SENSOR_GPIO_Port GPIOA
#define TempSens1_Pin GPIO_PIN_2
#define TempSens1_GPIO_Port GPIOA
#define MQ7_Pin GPIO_PIN_3
#define MQ7_GPIO_Port GPIOA
#define BIZZER_Pin GPIO_PIN_4
#define BIZZER_GPIO_Port GPIOA
#define TERMISTOR_1_Pin GPIO_PIN_5
#define TERMISTOR_1_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOB
#define KEY1_EXTI_IRQn EXTI0_IRQn
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOB
#define KEY2_EXTI_IRQn EXTI1_IRQn
#define LED_SIGNAL_1_Pin GPIO_PIN_2
#define LED_SIGNAL_1_GPIO_Port GPIOB
#define SSD1_Pin GPIO_PIN_12
#define SSD1_GPIO_Port GPIOB
#define SSD2_Pin GPIO_PIN_13
#define SSD2_GPIO_Port GPIOB
#define SSD3_Pin GPIO_PIN_14
#define SSD3_GPIO_Port GPIOB
#define Socket12V_Pin GPIO_PIN_15
#define Socket12V_GPIO_Port GPIOB
#define LCD_RESET_Pin GPIO_PIN_8
#define LCD_RESET_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_9
#define USART_TX_GPIO_Port GPIOA
#define TGS2600_HEATER_Pin GPIO_PIN_10
#define TGS2600_HEATER_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_11
#define LCD_DC_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_3
#define SPI1_SCK_GPIO_Port GPIOB
#define LED_SIGNAL_2_Pin GPIO_PIN_4
#define LED_SIGNAL_2_GPIO_Port GPIOB
#define SSD4_Pin GPIO_PIN_5
#define SSD4_GPIO_Port GPIOB
#define I2C_SCL_Pin GPIO_PIN_6
#define I2C_SCL_GPIO_Port GPIOB
#define USART_RX_Pin GPIO_PIN_7
#define USART_RX_GPIO_Port GPIOB
#define IR_MOTION_SENSOR_Pin GPIO_PIN_8
#define IR_MOTION_SENSOR_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define CO_SENSORS_QUANTITY 1

#define DAY_KVT_ADDR 0x0014
#define NIGHT_KVT_ADDR 0x001E
#define BEGIN_DATE_KVT_ADDR 0x0028
	
#define FIRST_PRESSING_EDGE_MS 2000
#define SECOND_PRESSING_EDGE_MS 5000
	
#define LCD_ADDR (0x27 << 1)     
#define LCD_SWITCH_OFF_TICKS 120000	
	
#define MENU_ITEMS_QUANT 168	
#define CHAR_BUFF_SIZE 4	 
#define EXECUTE_STEP_PERIOD_SEC 1	
	
#define MAX_OBJECT_NAME_LENGHT	16
#define MAX_CHARS_IN_SCREEN	16	
	
#define FIRST_FLASH_ADDRESS 2	
	
	//#define USE_DS1307
	#define USE_DS3231	
	
	extern uint8_t SETUP_MODE;
	extern 	char CO[3];
		
		
#define _LCDELEMENTS_
#define _MODE_
#define _PCOUNTERS_
#define _MENU_
	
#define TERMISTOR_TYPE_INDEX 1
#define CO_SENSOR_TYPE_INDEX 2
#define LIGHT_SENSOR_TYPE_INDEX 3
#define HUMIDITY_SENSOR_TYPE_INDEX 4	
	
#define MENU_ELEMENT_TYPE_INDEX 1
#define INT_SELECTOR_MENU_ELEMENT_TYPE_INDEX 2
#define OCJECT_SELECTOR_MENU_ELEMENT_TYPE_INDEX 3
	
	
	
/* USER CODE END Private defines */

#ifdef __cplusplus
}

#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
