#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

#include "uartDriver.h"

#define TXD_PIN (GPIO_NUM_27)
#define RXD_PIN (GPIO_NUM_26)


void uart_init(void);
int uart_sendData(const char *logName, const char *data);
void uart_tx_task(void *arg);
void uart_rx_task(void *arg);
void run_uart_tests(void);
