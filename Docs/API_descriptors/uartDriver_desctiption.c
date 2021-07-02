/**
* UART driver description
*/

typedef enum {
	UART_DriverRetVal_OK = 0,
	UART_DriverRetVal_NOK,
	UART_DriverRetVal_End
} UART_DriverRetVal_e;

typedef enum {
	UART_DriverUARTPeripheral1 = 0,
	UART_DriverUARTPeripheral2,
	UART_DriverUARTPeripheral3,
	UART_DriverUARTPeripheral_End
} UART_DriverUARTPeripheralList_e;

typedef struct {
	ESP32IDFUARTDriverType uartPeripheral;
	uint32_t UART_TxGPIO_PORT;
	uint32_t UART_RxGPIO_PORT;
	uint32_t UART_TxGPIO_PIN;
	uint32_t UART_RxGPIO_PIN;
} UART_DriverUARTInit_s;

static UART_DriverUARTInit_s UART_DriverUARTPeripherals[UART_DriverUARTPeripheral_End] =
{
	[UART_DriverUARTPeripheral1] = {
		.uartPeripheral.Instance 	= &ESP32UART1_Driver;
		.uartPeripheral.Baudrate 	= 115200,
		.uartPeripheral.StopBit 	= 1,
		.uartPeripheral.Parity 		= 0,
		.UART_TxGPIO_PORT 			= PORTA,
		.UART_RxGPIO_PORT 			= PORTA,
		.UART_TxGPIO_PIN 			= PIN0,
		.UART_RxGPIO_PIN 			= PIN1
	},
	[UART_DriverUARTPeripheral2] = {
		.uartPeripheral.Instance 	= &ESP32UART2_Driver;
		.uartPeripheral.Baudrate 	= 115200,
		.uartPeripheral.StopBit 	= 1,
		.uartPeripheral.Parity 		= 0,
		.UART_TxGPIO_PORT 			= PORTA,
		.UART_RxGPIO_PORT 			= PORTA,
		.UART_TxGPIO_PIN 			= PIN0,
		.UART_RxGPIO_PIN 			= PIN1
	}
};


static UART_Peripheral_s* UART_DriverGetPeripheralReference(UART_DriverUARTPeripheralList_e uartPeripheral_i)
{
	return &UART_DriverUARTPeripherals[uartPeripheral_i].Instance;
}

void UART_DriverInit(void);
void UART_DriverDeInit(void);

/*
1. Interrupt handling (Rx interrupt)
2. Polling mode
*/

UART_DriverRetVal_e UART_DriverSendByte(UART_DriverUARTPeripheralList_e uartPeripheral_i, uint8_t data_i)
{
	ESP32uartDriver_SendByte( UART_DriverGetPeripheralReference(uartPeripheral_i), data_i);
}

UART_DriverRetVal_e UART_DriverSendData(UART_DriverUARTPeripheralList_e uartPeripheral_i, uint8_t* pData_i, uint16_t length_i);
UART_DriverRetVal_e UART_DriverReceiveByte(UART_DriverUARTPeripheralList_e uartPeripheral_i, uint8_t* pData_o);
UART_DriverRetVal_e UART_DriverReceiveData(UART_DriverUARTPeripheralList_e uartPeripheral_i, uint8_t* pData_o, uint16_t length_i);

