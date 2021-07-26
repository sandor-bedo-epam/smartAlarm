#pragma once

#include <stdio.h>
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gpioDriver.h"

#define LED1_GPIO 26
#define LED2_GPIO 25
#define BUTTON1_GPIO 34
#define PIN_TOGGLE_DELAY_MS 1000

void gpio_driver_out_task(void *pvParameter);
