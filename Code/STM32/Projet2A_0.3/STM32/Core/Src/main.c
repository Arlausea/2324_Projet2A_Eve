/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

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
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART3_UART_Init();
  MX_USB_OTG_HS_USB_Init();
  MX_TIM4_Init();
  MX_UART5_Init();
  MX_SPI1_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,0); //Permet de configurer le TMC2590 à l'état bas donc de le sélectionner pour l'asservir

	int txData;
	int rxData;

	//txData = ordre(60);




	HAL_SPI_Init(&hspi1);
//
//
//
//	//HAL_SPI_Transmit_IT(&hspi1, datax, 1);
//
//
//	uint8_t data2[] = {0x09, 0x42, 0xD7};
//	//int status = HAL_SPI_Transmit_IT(&hspi1, data2, 3);  //Chop COnf
//
//
//
//
//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,0);
//	uint8_t data3[] = {0x0A, 0x00, 0x00};
//	//HAL_SPI_Transmit(&hspi1, data3, 3, HAL_MAX_DELAY);
//	// CoolStep /Smarten
//
//
//
//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,0);
//	uint8_t data4[] = {0x0D, 0x00, 0x0F};
//	//HAL_SPI_Transmit(&hspi1, data4, 3, HAL_MAX_DELAY);
//	// SGCSCONF
//
//	//HAL_SPI_Receive(&hspi1,rxData,1,HAL_MAX_DELAY);
//
//
//	uint8_t data5[] = {0x0E, 0xF0, 0x8F};
//
//	//HAL_SPI_Transmit(&hspi1, data5, 3, HAL_MAX_DELAY);
//	// DRVCONF
//
	HAL_GPIO_WritePin(Driver_EN_GPIO_Port, Driver_EN_Pin, SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */




		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, RESET);
		uint8_t data1[] = {0x94,0x2D,0x70};
		HAL_SPI_Transmit(&hspi1, data1, 3, 100);
		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, SET);
		HAL_Delay(1);
//
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, RESET);
//		uint8_t data2[] = {0x00, 0x00, 0x0A};
//		HAL_SPI_Transmit(&hspi1, data2, 1, 100);
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, SET);
//		HAL_Delay(1);
//
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, RESET);
//		uint8_t data3[] = {0x0F, 0x00, 0x0D};
//		HAL_SPI_Transmit(&hspi1, data3, 1, 100);
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, SET);
//		HAL_Delay(1);
//
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, RESET);
//		uint8_t data4[] = {0x8F, 0xF0, 0x0E};
//		HAL_SPI_Transmit(&hspi1, data4, 1, 100);
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, SET);
//		HAL_Delay(1);
//
//
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, RESET);
//		uint8_t data5[] = {0xE9, 0x56, 0x00};
//		HAL_SPI_Transmit(&hspi1, data5, 1, 100);
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, SET);
//		HAL_Delay(1);
//
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, RESET);
//		uint8_t data6[] = {0x56, 0xE9, 0x00};
//		HAL_SPI_Transmit(&hspi1, data6, 1, 100);
//		HAL_GPIO_WritePin(nCS_GPIO_Port, nCS_Pin, SET);
//		HAL_Delay(100);

		//HAL_SPI_Transmit_IT(&hspi1, data2, 3);  //Chop COnf
		//HAL_Delay(1);
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /*AXI clock gating */
  RCC->CKGAENR = 0xFFFFFFFF;

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 24;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* SPI1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(SPI1_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
