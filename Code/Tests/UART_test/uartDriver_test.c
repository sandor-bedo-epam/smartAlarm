/* UART driver test example, that uses separate RX and TX tasks

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "uartDriver_test.h"

static const char tag[] = "uartDriver Test";

static const int RX_BUF_SIZE = 511;
static const int TEST_UART_NUM = UART_NUM_2;

UART_DriverUARTConfig_s UART2_config = {.UART_number = TEST_UART_NUM,
                                        .UART_baud_rate = 115200,
                                        .UART_data_bits = 8,
                                        .UART_stop_bits = 1,
                                        .UART_parity = UART_DriverParity_Disable,
                                        .UART_TxBuff_Size = STD_UART_BUF_SIZE,
                                        .UART_RxBuff_Size = STD_UART_BUF_SIZE,
                                        .UART_TxGPIO_Pin = GPIO_NUM_27,
                                        .UART_RxGPIO_Pin = GPIO_NUM_26};

typedef enum
{
    UART_DriverUARTPeripheral1 = 0,
    UART_DriverUARTPeripheral2,
    UART_DriverUARTPeripheral_End
} UART_DriverUARTPeripheralList_e;

static UART_DriverUARTConfig_s UART_DriverUARTPeripherals[UART_DriverUARTPeripheral_End] =
    {
        [UART_DriverUARTPeripheral1] = {
            .UART_number = UART_NUM_1,
            .UART_baud_rate = 115200,
            .UART_data_bits = 8,
            .UART_stop_bits = 1,
            .UART_parity = UART_DriverParity_Disable,
            .UART_TxBuff_Size = STD_UART_BUF_SIZE,
            .UART_RxBuff_Size = STD_UART_BUF_SIZE,
            .UART_TxGPIO_Pin = GPIO_NUM_17,
            .UART_RxGPIO_Pin = GPIO_NUM_16},
        [UART_DriverUARTPeripheral2] = {.UART_number = UART_NUM_2, .UART_baud_rate = 115200, .UART_data_bits = 8, .UART_stop_bits = 1, .UART_parity = UART_DriverParity_Disable, .UART_TxBuff_Size = STD_UART_BUF_SIZE, .UART_RxBuff_Size = STD_UART_BUF_SIZE, .UART_TxGPIO_Pin = GPIO_NUM_27, .UART_RxGPIO_Pin = GPIO_NUM_26}};

void uart_init(void)
{

    if (UART_Driver_MultiInit(UART_DriverUARTPeripherals, UART_DriverUARTPeripheral_End) == UART_DriverRetVal_OK)
    {
        ESP_LOGI(tag, "UART Init successful");
    }
    else
    {
        ESP_LOGE(tag, "UART Init failed");
    }
}

void uart_tx_task(void *arg)
{
    static const char *TX_TASK_TAG = "TX_TASK UART1";
    static char msg_to_send[] = "Holzkoffer for president";
    int total_sent_bytes;
    total_sent_bytes = 0;
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    vTaskDelay(pdMS_TO_TICKS(500));
    while (total_sent_bytes < 600)
    {
        UART_DriverSendByte(&UART_DriverUARTPeripherals[UART_DriverUARTPeripheral1], 0x45);
        total_sent_bytes++;
        UART_DriverSendByte(&UART_DriverUARTPeripherals[UART_DriverUARTPeripheral1], 0x21);
        total_sent_bytes++;
        UART_DriverSendData(&UART_DriverUARTPeripherals[UART_DriverUARTPeripheral1], msg_to_send, sizeof(msg_to_send) - 1);
        total_sent_bytes = total_sent_bytes + (sizeof(msg_to_send) - 1);
        ESP_LOGI(TX_TASK_TAG, "Sent total %d bytes so far", total_sent_bytes);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TX_TASK_TAG, "UART1 sending finished");
    //UART_DriverUARTDeInit(&UART_DriverUARTPeripherals[UART_DriverUARTPeripheral1]);
    UART_Driver_MultiDeInit(UART_DriverUARTPeripherals, UART_DriverUARTPeripheral_End);
    vTaskDelete(NULL);
}

void uart_rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK UART2";
    int rx_bytes;
    int total_rx_bytes;
    total_rx_bytes = 0;
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
    while (total_rx_bytes < 512)
    {

        rx_bytes = UART_DriverReceiveData(&UART_DriverUARTPeripherals[UART_DriverUARTPeripheral2], data, 31);
        if (rx_bytes > 0)
        {
            data[rx_bytes] = 0;
            total_rx_bytes = total_rx_bytes + rx_bytes;
            ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rx_bytes, data);
            ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rx_bytes, ESP_LOG_INFO);
        }
        else
        {
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }
    free(data);
    ESP_LOGI(RX_TASK_TAG, "UART2 receiving finished");
    uart_flush(UART_DriverUARTPeripherals[UART_DriverUARTPeripheral2].UART_number);
    vTaskDelete(NULL);
}

void run_uart_tests(void)
{
    uart_init();
    vTaskDelay(100 / portTICK_PERIOD_MS);

    xTaskCreate(uart_rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);
    xTaskCreate(uart_tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
}
