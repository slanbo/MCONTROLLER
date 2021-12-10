/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "thread.hpp"
#include "ticks.hpp"
#include "semaphore.hpp"
#include "task.h"
#include "stm32_ds3231.h"
#include "ds1307_for_stm32_hal.h"
#include "Auxiliary.h"
#include "string.h"
#include "math.h"
#include "Buttons.hpp"
#include "Bizzer.hpp"
#include "MenuClass.hpp"


#include "Font.h"
#include "LCDFonts.hpp"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

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
void SystemClock_Config(void);
//void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t SETUP_MODE = 0;     // 
Bizzer alarmBizzer("Aloarm bizzer", BIZZER_GPIO_Port, BIZZER_Pin);

//+++++++++++++++++++ LCDFont ++++++++++++++++++
LCDFont Verdana12x12(Verdana12x12Rus, Verdana12x12Eng, 12);

//++++++++++++++++ TUNES +++++++++++++++++++++++++++++++
#include "TuneObjects.hpp"
//+++++++++++++ SCREEN ELEMENTS ++++++++++++++++
#include "ScreenObjects.hpp"
//++++++++++++++ LCD Elements ++++++++++++++++++++
#include "ADCDevObjects.hpp"
#include "SensorObjects.hpp"
//++++++++++++++++++ SOCKETS ++++++++++++++++++++++++++++++++
#include "SocketObjects.hpp"
//+++++++++++++++++ TIME PROFILES ++++++++++++++++++++++
#include "TimeProfileObjects.hpp"
//+++++++++++++++++ PAUSES ++++++++++++++++++++++++++
#include "TempPausesObjects.hpp"
//++++++++++++++++ CONTROLS ++++++++++++++++++++++++++
#include "ControlObjects.hpp"
//+++++++++++++ MODES ++++++++++++++++
#include "ModeObjects.hpp"

//++++++++++++++++++ MENU ++++++++++++++++++++++++++++++++
#include "MenuElementObjects.hpp"

//++++++++++++++++++ PCOUNTERS ++++++++++++++++++++++++++++++++
#include "PCounterObjects.hpp"


//+++++++++++++++++++++ THREADS ++++++++++++++++++++++++++++
#include "RenderInfoThread.hpp"
#include "RenderTopBottomThread.hpp"
#include "FillScreenThread.hpp"
#include "ADCThread.hpp"
#include "MotionDetectionThread.hpp"
#include "ExecuteStepThread.hpp"
#include "PCounterThread.hpp"
#include "UsartThread.hpp"
#include "BizzerThread.hpp"
#include "ProcessButtonPressedThread.hpp"

uint32_t lastTimeTicksButtonsPressed = 0;
uint8_t leftButtonShortPressCounter = 0;
uint8_t leftButtonLongPressCounter = 0;
uint8_t leftButtonLongLongPressCounter = 0;
uint8_t rightButtonShortPressCounter = 0;
uint8_t rightButtonLongPressCounter = 0;
uint8_t rightButtonLongLongPressCounter = 0;
uint8_t bothButtonsPressCounter = 0;

uint8_t showInfoCounter = 0;
uint8_t currentPCounter = 0;


FillScreen* fscr = new FillScreen("fscr", 1, EXECUTE_STEP_PERIOD_SEC, 7);
RenderInfoScreen* ris = new RenderInfoScreen("ris", 2, EXECUTE_STEP_PERIOD_SEC, 6);
ExecuteModeStep ems("ems", 4, EXECUTE_STEP_PERIOD_SEC, 5);
processButtonsPressed pbp("pbp", 6, EXECUTE_STEP_PERIOD_SEC, 4);
getADCVols gADCV("gADCV", 5, EXECUTE_STEP_PERIOD_SEC, 3);
menuButtonPressBizzer mbpb("mbpb", 6, 100, 2);
bizzerExecuteStep bes("bes", 8, 100, 1);


PCountersExecuteStep pcES("pcES", 9, EXECUTE_STEP_PERIOD_SEC, 1);

 SemaphoreHandle_t lcdmut_handle;


 Menu* mainMenu;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	
	
	/* USER CODE BEGIN 1 */
	

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_I2C1_Init();
	MX_RTC_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_ADC1_Init();
	MX_USART1_UART_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */
	
	/*HAL_GPIO_WritePin(SSD1_GPIO_Port, SSD1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SSD2_GPIO_Port, SSD2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SSD3_GPIO_Port, SSD3_Pin, GPIO_PIN_SET); //down socket
	HAL_GPIO_WritePin(Socket12V_GPIO_Port, Socket12V_Pin, GPIO_PIN_SET);*/
	
	HAL_TIM_Base_Start(&htim1);
	
#ifdef USE_DS1307
	
	DS1307_Init(&hi2c1);	
	//DS1307_setDateTime(07, 04, 2021, 21, 14, 00, 4);
	
#endif //USE_DS1307 

//#ifdef USE_DS3231
	DS3231_Init(&hi2c1);
	
	//_RTC rtc;
	//rtc.Year = 21;
	//rtc.Month = 11;
	//rtc.Date = 27;
	//rtc.Hour = 22;
	//rtc.Min = 44;
	//rtc.Sec = 0;
	//rtc.DaysOfWeek = 6;
	
	//DS3231_SetTime(&rtc);
	
//#endif //USE_DS3231 
	
	set_RTC_From_DS();
		
	
	//INITS 
	Lcd_Init();	
	Lcd_Init();	
	Lcd_Init();	
	Lcd_Clear(RED);
	Lcd_Clear(YELLOW);
	Lcd_Clear(GREEN);
	Lcd_Clear(BLACK);
	
	HAL_FLASH_Unlock();
	EE_Init();
	HAL_FLASH_Lock();
	
	readTunesFromFlash();
	setDefaultTuneVals();
	
	postInitStaticMenuElements(&mi_167);
	
	ModeObjectsInit();
	mainMenu = new Menu(&mi_0);
	
	lcdmut_handle = xSemaphoreCreateMutex();
	
	
	/*uint8_t rsvdt[80];
	
	uint8_t strrst[] = "AT+RST\r\n";
	HAL_UART_Transmit(&huart1, strrst, sizeof(strrst), 0xFF);
	HAL_UART_Receive(&huart1, (uint8_t *)&rsvdt, 80, 0xFF);

	uint8_t strate0[] = "ATE0\r\n";
	HAL_UART_Transmit(&huart1, strate0, sizeof(strate0), 0xFF);
	HAL_UART_Receive(&huart1, (uint8_t *)&rsvdt, 80, 0xFF);*/
	
	Thread::StartScheduler();
	/* USER CODE END 2 */

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while(1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 15;
	RCC_OscInitStruct.PLL.PLLN = 144;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 5;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
	                            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM3) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	 /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
