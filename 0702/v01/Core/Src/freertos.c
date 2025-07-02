/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Button.h"
#include "LedBar.h"
#include "my_queue.h"
#include "lcd.h"
#include <stdio.h>
#include "tim.h"
#include "FND.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum {BTN_LED1, BTN_LED2, BTN_LED3};
enum {BTN_START, BTN_STOP, BTN_CLEAR};

typedef struct{
	int id;
}btn_led_t;

typedef struct{
	int id;
}btn_fnd_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osMailQDef(btnMail, 4, btn_led_t);
osMailQId btnMail;

osMailQDef(btnFNDMail, 4, btn_fnd_t);
osMailQId btnFNDMail;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myButtonTaskHandle;
osThreadId myLedTaskHandle;
osThreadId myFNDTaskHandle;
osMessageQId btnLedQueueHandle;
osMutexId LcdMutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartButtonTask(void const * argument);
void StartLedTask(void const * argument);
void StartFNDTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */


  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of LcdMutex */
  osMutexDef(LcdMutex);
  LcdMutexHandle = osMutexCreate(osMutex(LcdMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */

  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of btnLedQueue */
  osMessageQDef(btnLedQueue, 16, uint16_t);
  btnLedQueueHandle = osMessageCreate(osMessageQ(btnLedQueue), NULL);


  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  btnMail=osMailCreate(osMailQ(btnMail), NULL);
  btnFNDMail=osMailCreate(osMailQ(btnFNDMail), NULL);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myButtonTask */
  osThreadDef(myButtonTask, StartButtonTask, osPriorityNormal, 0, 128);
  myButtonTaskHandle = osThreadCreate(osThread(myButtonTask), NULL);

  /* definition and creation of myLedTask */
  osThreadDef(myLedTask, StartLedTask, osPriorityNormal, 0, 128);
  myLedTaskHandle = osThreadCreate(osThread(myLedTask), NULL);

  /* definition and creation of myFNDTask */
  osThreadDef(myFNDTask, StartFNDTask, osPriorityNormal, 0, 128);
  myFNDTaskHandle = osThreadCreate(osThread(myFNDTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  HAL_TIM_Base_Start_IT(&htim2);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartButtonTask */
/**
* @brief Function implementing the myButtonTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartButtonTask */
void StartButtonTask(void const * argument)
{
  /* USER CODE BEGIN StartButtonTask */
	Button_Init(&hBtnLed1, GPIOB, GPIO_PIN_5);
	Button_Init(&hBtnLed2, GPIOB, GPIO_PIN_3);
	Button_Init(&hBtnLed3, GPIOA, GPIO_PIN_10);

	LCD_Init(&hi2c1);

//	MyQue_Init(&qBtnLed, sizeof(btn_led_t));
	btn_led_t *btnData;
	btn_fnd_t *btnFND;
	char str[30];
	uint32_t counter =0;

	/* Infinite loop */
  for(;;)
  {
	  if(Button_GetState(&hBtnLed1) == ACT_RELEASED){
		  btnData = osMailAlloc(btnMail, osWaitForever);
		  btnFND = osMailAlloc(btnFNDMail, osWaitForever);
		  btnData -> id = BTN_LED1;
		  btnFND -> id = BTN_START;
		  osMailPut(btnMail, btnData);
		  osMailPut(btnFNDMail, btnFND);
//		  MyenQue(&qBtnLed,&btnData);

		  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 비어있을 때 까지 기다림. 비어있으면 문닫고 문 잠금
		  LCD_writeStringXY(0, 0, "BTN1");
		  osMutexRelease(LcdMutexHandle); //화장실 문 염
	  }
	  else if(Button_GetState(&hBtnLed2) == ACT_RELEASED){
		  btnData = osMailAlloc(btnMail, osWaitForever);
		  btnFND = osMailAlloc(btnFNDMail, osWaitForever);
		  btnData->id = BTN_LED2;
		  btnFND -> id = BTN_STOP;
		  osMailPut(btnMail, btnData);
		  osMailPut(btnFNDMail, btnFND);

//		  MyenQue(&qBtnLed, &btnData);
		  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
		  LCD_writeStringXY(0, 0, "BTN2");
		  osMutexRelease(LcdMutexHandle); //화장실 문 염
	  }
	  else if(Button_GetState(&hBtnLed3) == ACT_RELEASED){
		  btnData = osMailAlloc(btnMail, osWaitForever);
		  btnFND = osMailAlloc(btnFNDMail, osWaitForever);
		  btnData->id = BTN_LED3;
		  btnFND -> id = BTN_CLEAR;
		  osMailPut(btnMail, btnData);
		  osMailPut(btnFNDMail, btnFND);

//		  MyenQue(&qBtnLed, &btnData);
		  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
		  LCD_writeStringXY(0, 0, "BTN3");
		  osMutexRelease(LcdMutexHandle); //화장실 문 염

	  }
	  sprintf(str, ":cnt %u", (unsigned int)counter++);
	  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
	  LCD_writeStringXY(0, 5, str);
	  osMutexRelease(LcdMutexHandle); //화장실 문 염
	  osDelay(10);
  }
  /* USER CODE END StartButtonTask */
}

/* USER CODE BEGIN Header_StartLedTask */
/**
* @brief Function implementing the myLedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLedTask */
void StartLedTask(void const * argument)
{
  /* USER CODE BEGIN StartLedTask */
	btn_led_t *btnData;
	osEvent evt;

	uint8_t ledData =0;
	uint32_t prevTime =0, curTime =0;
	char str[30];
	uint32_t count =0;
  /* Infinite loop */
  for(;;)
  {
	  curTime = HAL_GetTick();
	  if(curTime - prevTime >=500){
		  prevTime = curTime;
		  ledData ^= (1<<0);
		  LedBar_Write(ledData);
	  }

	  evt = osMailGet(btnMail, 0);
	  if (evt.status == osEventMail){
		  btnData = evt.value.p; //주소를 넣어주는 것

		  if(btnData->id == BTN_LED1){
			  ledData ^= (1 << 1);
			  LedBar_Write(ledData);
			  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
			  LCD_writeStringXY(1, 0, "LED1");
			  osMutexRelease(LcdMutexHandle); //화장실 문 염

		  }else if (btnData->id == BTN_LED2){
			  ledData ^= (1 << 2);
			  LedBar_Write(ledData);
			  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
			  LCD_writeStringXY(1, 0, "LED2");
			  osMutexRelease(LcdMutexHandle); //화장실 문 염

		  } else if (btnData->id == BTN_LED3){
			  ledData ^= (1 << 3);
			  LedBar_Write(ledData);
			  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
			  LCD_writeStringXY(1, 0, "LED3");
			  osMutexRelease(LcdMutexHandle); //화장실 문 염
		  }else{
			  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
			  LCD_writeStringXY(1, 0, "LEDx");
			  osMutexRelease(LcdMutexHandle); //화장실 문 염

		  }
		  osMailFree(btnMail, btnData);
	  }
	  sprintf(str, ":cnt %u", (unsigned int)count++);
	  osMutexWait(LcdMutexHandle, osWaitForever); //화장실 문닫고 문 잠금
	  LCD_writeStringXY(1, 5, str);
	  osMutexRelease(LcdMutexHandle); //화장실 문 염
	  osDelay(100);
  }
  /* USER CODE END StartLedTask */
}

/* USER CODE BEGIN Header_StartFNDTask */
/**
* @brief Function implementing the myFNDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFNDTask */
void StartFNDTask(void const * argument)
{
  /* USER CODE BEGIN StartFNDTask */
	uint16_t counter=0;
	btn_fnd_t *btnFND;
	osEvent evt;
	typedef enum {STOP, START, CLEAR}stopWatchState_t;
	stopWatchState_t watchState=STOP;
	  /* Infinite loop */
	  for(;;)
	  {
		  evt = osMailGet(btnFNDMail, 0);
		  if (evt.status == osEventMail){
			  btnFND = evt.value.p; //주소를 넣어주는 것
			  if(btnFND->id == BTN_START){
				 watchState = START;
			  }else if (btnFND->id == BTN_STOP){
				  watchState = STOP;
			  } else if (btnFND->id == BTN_CLEAR){
				  watchState = CLEAR;
			  }
			  osMailFree(btnFNDMail, btnFND);
		  }
	  switch (watchState){
	  case START:
		  counter++;
		  break;
	  case CLEAR:
		  counter =0;
		  break;
	  }
    FND_WriteData(counter);
    osDelay(10);
	  }
  /* USER CODE END StartFNDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
