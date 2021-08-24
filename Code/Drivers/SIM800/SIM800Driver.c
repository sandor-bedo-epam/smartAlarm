#include "SIM800Driver.h"

static const char tag[] = "SIM800Driver";

static SIM800_Command_s cmd_AT = {.command = "AT\r\n",
                                  .responseOnOk = SIM800_OK_Str, // handle multiple OK responses!
                                  .responseOnNotOk = {"1", "", ""},
                                  .numOfNotOkResponses = 1,
                                  .timeoutMs = 250,
                                  .delayMs = 50};

static SIM800_Command_s cmd_ATinfo = {.command = "ATI\r\n",
                                      .responseOnOk = "\r\nSIM800",
                                      .responseOnNotOk = {"1", "", ""},
                                      .numOfNotOkResponses = 1,
                                      .timeoutMs = 250,
                                      .delayMs = 50};

SIM800_DriverRetVal_e SIM800_DriverSIM800_Init(SIM800_DriverSIM800Config_s *pSIM800Modem_i)
{
    uint8_t rx_buffer[32];
    int rx_bytes;

    SIM800_DriverRetVal_e driverRetVal;
    driverRetVal = SIM800_DriverRetVal_OK;
    ESP_LOGI(tag, "Initializing SIM800 modem");
    do
    {
        if (gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_PWKEY)) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        if (gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_RST)) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        if (gpioDriverPinInit_Output(&(pSIM800Modem_i->Pin_POWERON)) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
    } while (0);
    vTaskDelay(pdMS_TO_TICKS(10));

    while (driverRetVal == SIM800_DriverRetVal_OK)
    {
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_POWERON), GPIO_DriverGPIOLevel_High) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_RST), GPIO_DriverGPIOLevel_High) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_PWKEY), GPIO_DriverGPIOLevel_Low) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
        if (UART_DriverUARTInit(&(pSIM800Modem_i->SIM800_UART)) != UART_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_PWKEY), GPIO_DriverGPIOLevel_High) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(SIM800_PWKEY_PULSE_WAIT));
        if (gpioDriverSetPin_Level(&(pSIM800Modem_i->Pin_PWKEY), GPIO_DriverGPIOLevel_Low) != GPIO_DriverRetVal_OK)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        break;
    }

    while (driverRetVal == SIM800_DriverRetVal_OK)
    {
        vTaskDelay(pdMS_TO_TICKS(SIM800_INIT_WAIT));
        ESP_LOGI(tag, "Testing SIM800 modem's response to AT command");
        UART_DriverSendData(&(pSIM800Modem_i->SIM800_UART), cmd_AT.command, strlen(cmd_AT.command));
        vTaskDelay(pdMS_TO_TICKS(cmd_AT.delayMs));
        memset(rx_buffer, 0, sizeof(rx_buffer));
        rx_bytes = UART_DriverReceiveData(&(pSIM800Modem_i->SIM800_UART), rx_buffer, sizeof(rx_buffer) - 1);
        if (strcmp((char *)rx_buffer, cmd_AT.responseOnOk) != 0)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            break;
        }
        ESP_LOGI(tag, "Testing SIM800 modem's response to ATI command");
        UART_DriverSendData(&(pSIM800Modem_i->SIM800_UART), cmd_ATinfo.command, strlen(cmd_ATinfo.command));
        vTaskDelay(pdMS_TO_TICKS(cmd_ATinfo.delayMs));
        memset(rx_buffer, 0, sizeof(rx_buffer));
        rx_bytes = UART_DriverReceiveData(&(pSIM800Modem_i->SIM800_UART), rx_buffer, sizeof(rx_buffer) - 1);
        ESP_LOGI(tag, "Read %d bytes: '%s'", rx_bytes, rx_buffer);
        ESP_LOG_BUFFER_HEXDUMP(tag, rx_buffer, rx_bytes, ESP_LOG_INFO);
        rx_buffer[strlen(cmd_ATinfo.responseOnOk)] = 0;
        if (strcmp((char *)rx_buffer, cmd_ATinfo.responseOnOk) != 0)
        {
            driverRetVal = SIM800_DriverRetVal_NOK;
            ESP_LOGE(tag, "Response to ATI command is not OK");
            break;
        }

        break;
    }

    return driverRetVal;
}
