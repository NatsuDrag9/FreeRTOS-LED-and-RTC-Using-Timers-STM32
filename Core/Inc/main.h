/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef struct {
	uint8_t payload[10];
	uint8_t length;
} command_t;

// Application states for this project
typedef enum{
	state_MainMenu = 0,
	state_LedEffect,
	state_RtcMenu,
	state_RtcTimeConfig,
	state_RtcDateConfig,
	state_RtcReport,
}state_t;

extern TaskHandle_t handle_menu_task;
extern TaskHandle_t handle_cmd_task;
extern TaskHandle_t handle_print_task;
extern TaskHandle_t handle_led_task;
extern TaskHandle_t handle_rtc_task;

extern QueueHandle_t q_data_input;
extern QueueHandle_t q_data_print;

extern volatile uint8_t user_data;

extern state_t current_state;

extern TimerHandle_t handle_led_timers[3];
extern TimerHandle_t rtc_timer;

extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart3;
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

void menu_task_handler(void*);
void cmd_task_handler(void*);
void print_task_handler(void*);
void led_task_handler(void*);
void rtc_task_handler(void*);

void led_effect_stop(void);
void led_effect(int);

void LED_Effect1();
void LED_Effect2();
void LED_Effect3();

void show_date_time(void);
void rtc_config_time(RTC_TimeTypeDef*);
void rtc_config_date(RTC_DateTypeDef*);
int validate_rtc(RTC_TimeTypeDef*, RTC_DateTypeDef*);
void show_date_time_itm(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define HH_CONFIG 0
#define MM_CONFIG 1
#define SS_CONFIG 2
#define TIME_FORMAT_CONFIG 3

#define DATE_CONFIG 0
#define MONTH_CONFIG 1
#define YEAR_CONFIG 2
#define DAY_CONFIG 3
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
