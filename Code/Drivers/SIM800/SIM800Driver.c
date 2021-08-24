#include "SIM800Driver.h"

static const char tag[] = "SIM800Driver";

static SIM800_Command_s cmd_AT = {.command = "AT\r\n",
                                  .commandSize = sizeof("AT\r\n") - 1,
                                  .responseOnOk = SIM800_OK_Str,
                                  .timeoutMs = 250,
                                  .delayMs = 100};

SIM800_DriverRetVal_e SIM800_DriverSIM800_Init(SIM800_DriverSIM800Config_s *pSIM800Modem_i)
{
    uint8_t rx_buffer[32];
    int     rx_bytes;

    SIM800_DriverRetVal_e driverRetVal;
    driverRetVal = SIM800_DriverRetVal_OK;
    if (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_PWKEY)) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
        }
    }
    if (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_RST)) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
        }
    }
    if (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_POWERON)) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
        }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
    if (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_PWKEY), GPIO_DriverGPIOLevel_Low) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
        }
    }
    if (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_RST), GPIO_DriverGPIOLevel_High) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
        }
    }
    if (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_POWERON), GPIO_DriverGPIOLevel_High) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
        }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
    if (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (UART_DriverUARTInit(&(pSIM800Modem_i->SIM800_UART)) != UART_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
        }
    }
    vTaskDelay(pdMS_TO_TICKS(SIM800_INIT_WAIT));
    ESP_LOGI(tag, "Initializing SIM800 modem");
    ESP_LOG_BUFFER_HEXDUMP(tag, cmd_AT.command, cmd_AT.commandSize, ESP_LOG_INFO);
    UART_DriverSendData(&(pSIM800Modem_i->SIM800_UART), cmd_AT.command, cmd_AT.commandSize);
    vTaskDelay(pdMS_TO_TICKS(cmd_AT.delayMs));
    memset(rx_buffer, 0, sizeof(rx_buffer));
    rx_bytes = UART_DriverReceiveData(&(pSIM800Modem_i->SIM800_UART), rx_buffer, sizeof(rx_buffer) - 1);
    ESP_LOGI(tag, "Read %d bytes: '%s'", rx_bytes, rx_buffer);
    ESP_LOG_BUFFER_HEXDUMP(tag, rx_buffer, rx_bytes, ESP_LOG_INFO);
    return driverRetVal;
}
