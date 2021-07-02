/*
* GPIO Driver for smartAlarm system
*/

#pragma once

#include <stdio.h>
#include "driver/gpio.h"

typedef enum {
	GPIO_DriverRetVal_OK = 0,
	GPIO_DriverRetVal_NOK,
	GPIO_DriverRetVal_End
} GPIO_DriverRetVal_e;

typedef enum {
	GPIO_DriverGPIOLed1_o = 0,
	GPIO_DriverGPIOLed2_o,
	GPIO_DriverGPIOButton1_i,
	GPIO_DriverGPIOButton2_i,
	GPIO_DriverGPIOPeripheral_End
} GPIO_DriverGPIOPeripheralList_e;

typedef enum {
	GPIO_DriverGPIO_MODE_DISABLE = 0,
	GPIO_DriverGPIO_MODE_INPUT,
	GPIO_DriverGPIO_MODE_OUTPUT,
	GPIO_DriverGPIO_MODE_OUTPUT_OD,
	GPIO_DriverGPIO_MODE_INPUT_OUTPUT_OD,
	GPIO_DriverGPIO_MODE_INPUT_OUTPUT
} GPIO_DriverGPIOMode_e;  // For ESP32 see gpio_pull_mode_t enum

typedef enum {
	GPIO_DriverGPIO_PULLUP_ONLY = 0,
	GPIO_DriverGPIO_PULLDOWN_ONLY,
	GPIO_DriverGPIO_PULLUP_PULLDOWN,
	GPIO_DriverGPIO_FLOATING
} GPIO_DriverGPIOPullMode_e;  // For ESP32 see gpio_mode_t enum

typedef enum {
	GPIO_DriverGPIOLevel_Low = 0,
	GPIO_DriverGPIOLevel_High = 1	
} GPIO_DriverGPIOLevel_e;

typedef struct {
	uint32_t GPIO_Pin_Port;
	uint32_t GPIO_Pin_Number;
	uint32_t GPIO_Mode; // Input or Output, maybe not needed?
	uint32_t GPIO_PullUpDown_Selector;
} GPIO_DriverGPIOInit_s;

static GPIO_DriverGPIOInit_s GPIO_DriverGPIOPeripherals[GPIO_DriverGPIOPeripheral_End] =
{
	[GPIO_DriverGPIOLed1_o] = {
		.GPIO_Pin_Port 				= 0,
		.GPIO_Pin_Number 			= 2,
		.GPIO_Mode 					= GPIO_DriverGPIO_MODE_OUTPUT,
		.GPIO_PullUpDown_Selector	= GPIO_DriverGPIO_FLOATING
	},
	[GPIO_DriverGPIOLed2_o] = {
		.GPIO_Pin_Port 				= 0,
		.GPIO_Pin_Number 			= 5,
		.GPIO_Mode 					= GPIO_DriverGPIO_MODE_OUTPUT,
		.GPIO_PullUpDown_Selector	= GPIO_DriverGPIO_FLOATING
	},
	[GPIO_DriverGPIOButton1_i] = {
		.GPIO_Pin_Port 				= 0,
		.GPIO_Pin_Number 			= 34,
		.GPIO_Mode 					= GPIO_DriverGPIO_MODE_INPUT,
		.GPIO_PullUpDown_Selector	= GPIO_DriverGPIO_PULLUP_ONLY
	},
	[GPIO_DriverGPIOButton2_i] = {
		.GPIO_Pin_Port 				= 0,
		.GPIO_Pin_Number 			= 35,
		.GPIO_Mode 					= GPIO_DriverGPIO_MODE_INPUT,
		.GPIO_PullUpDown_Selector	= GPIO_DriverGPIO_PULLUP_ONLY
	}
};

//GPIO_DriverRetVal_e gpioDriver_Init(void);
//GPIO_DriverRetVal_e gpioDriver_DeInit(void);

GPIO_DriverRetVal_e gpioDriverPinInit_Input(GPIO_DriverGPIOInit_s* pGPIOPin_i);
GPIO_DriverRetVal_e gpioDriverPinInit_Output(GPIO_DriverGPIOInit_s* pGPIOPin_i);
GPIO_DriverRetVal_e gpioDriverPinDeInit(GPIO_DriverGPIOInit_s* pGPIOPin_i);
GPIO_DriverRetVal_e gpioDriverSetPin_Level(GPIO_DriverGPIOInit_s* pGPIOPin_i, GPIO_DriverGPIOLevel_e eGPIOLevel_i);
GPIO_DriverRetVal_e gpioDriverTogglePin(GPIO_DriverGPIOInit_s* pGPIOPin_i);
//GPIO_DriverRetVal_e gpioDriverReadPin(uint32_t Pin_Port, uint32_t Pin_Number, uint8_t* pData_o);

