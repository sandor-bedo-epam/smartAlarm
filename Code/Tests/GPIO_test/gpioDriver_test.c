#include "gpioDriver_test.h"

static const char *TAG = "GPIO Driver Test";

static GPIO_DriverGPIOConfig_s GPIO_DriverGPIOPeripherals[GPIO_DriverGPIOPeripheral_End] =
    {
        [GPIO_DriverGPIOLed1_o] = {.GPIO_Pin_Port = 0, .GPIO_Pin_Number = 26, .GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT, .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING},
        [GPIO_DriverGPIOLed2_o] = {.GPIO_Pin_Port = 0, .GPIO_Pin_Number = 25, .GPIO_Mode = GPIO_DriverGPIO_MODE_OUTPUT, .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_FLOATING},
        [GPIO_DriverGPIOButton1_i] = {.GPIO_Pin_Port = 0, .GPIO_Pin_Number = 34, .GPIO_Mode = GPIO_DriverGPIO_MODE_INPUT, .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_PULLUP_ONLY},
        [GPIO_DriverGPIOButton2_i] = {.GPIO_Pin_Port = 0, .GPIO_Pin_Number = 35, .GPIO_Mode = GPIO_DriverGPIO_MODE_INPUT, .GPIO_PullUpDown_Selector = GPIO_DriverGPIO_PULLUP_ONLY}};

void gpio_driver_out_task(void *pvParameter)
{
    uint8_t i;
    uint8_t GPIO_level;
    GPIO_DriverGPIOConfig_s GPIO_pin_def_LED1;
    GPIO_DriverGPIOConfig_s GPIO_pin_def_BUTTON1;

    ESP_LOGI(TAG, "GPIO Driver Init Start");
    if (gpioDriver_Init(GPIO_DriverGPIOPeripherals, GPIO_DriverGPIOPeripheral_End) == GPIO_DriverRetVal_NOK)
    {
        ESP_LOGI(TAG, "GPIO Driver Init FAILED, exiting");
        vTaskDelete(NULL);
    }
    ESP_LOGI(TAG, "GPIO Driver Init Done");
    GPIO_pin_def_LED1 = GPIO_DriverGPIOPeripherals[GPIO_DriverGPIOLed1_o];
    GPIO_pin_def_BUTTON1 = GPIO_DriverGPIOPeripherals[GPIO_DriverGPIOButton1_i];
    ESP_LOGI(TAG, "Set GPIO Pin Level to High");
    gpioDriverSetPin_Level(&GPIO_pin_def_LED1, GPIO_DriverGPIOLevel_High);
    gpioDriverReadPin(&GPIO_pin_def_LED1, &GPIO_level);
    ESP_LOGI(TAG, "GPIO read level: %d", GPIO_level);
    vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    for (i = 0; i < 10; i++)
    {
        ESP_LOGI(TAG, "Toggle GPIO Pin Level");
        gpioDriverTogglePin(&GPIO_pin_def_LED1);
        gpioDriverReadPin(&GPIO_pin_def_LED1, &GPIO_level);
        ESP_LOGI(TAG, "GPIO LED1 read level: %d", GPIO_level);
        gpioDriverReadPin(&GPIO_pin_def_BUTTON1, &GPIO_level);
        ESP_LOGI(TAG, "GPIO BUTTON1 read level: %d", GPIO_level);
        vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    }
    ESP_LOGI(TAG, "Set GPIO Pin Level to Low");
    gpioDriverSetPin_Level(&GPIO_pin_def_LED1, GPIO_DriverGPIOLevel_Low);
    gpioDriverReadPin(&GPIO_pin_def_LED1, &GPIO_level);
    ESP_LOGI(TAG, "GPIO read level: %d", GPIO_level);
    vTaskDelay(PIN_TOGGLE_DELAY_MS / portTICK_RATE_MS);
    ESP_LOGI(TAG, "GPIO Driver DeInit");
    //gpioDriverPinDeInit(&GPIO_pin_def_LED1);
    gpioDriver_DeInit(GPIO_DriverGPIOPeripherals, GPIO_DriverGPIOPeripheral_End);
    ESP_LOGI(TAG, "GPIO Driver Task Stop");
    vTaskDelete(NULL);
}
