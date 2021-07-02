/**
* I2C driver description
*/

typedef enum {
	I2C_DriverRetVal_OK = 0,
	I2C_DriverRetVal_NOK,
	I2C_DriverRetVal_End
} I2C_DriverRetVal_e;

typedef enum {
	I2C_DriverI2CPeripheral1 = 0,
	I2C_DriverI2CPeripheral2,
	I2C_DriverI2CPeripheral_End
} I2C_DriverI2CPeripheralList_e;

typedef struct {
	ESP32IDFI2CDriverType i2cPeripheral;
	uint32_t I2C_SCL_GPIO_PORT;
	uint32_t I2C_SDA_GPIO_PORT;
	uint32_t I2C_SCL_GPIO_PIN;
	uint32_t I2C_SDA_GPIO_PIN;
} I2C_DriverI2CInit_s;

static I2C_DriverI2CInit_s I2C_DriverI2CPeripherals[I2C_DriverI2CPeripheral_End] =
{
	[I2C_DriverI2CPeripheral1] = {
		.i2cPeripheral.Instance 	= &ESP32I2C1_Driver;
		.i2cPeripheral.Speed 		= 400000,
		.I2C_SCL_GPIO_PORT 			= PORTA,
		.I2C_SDA_GPIO_PORT 			= PORTA,
		.I2C_SCL_GPIO_PIN 			= PIN0,
		.I2C_SDA_GPIO_PIN 			= PIN1
	},
	[I2C_DriverI2CPeripheral2] = {
		.i2cPeripheral.Instance 	= &ESP32I2C2_Driver;
		.i2cPeripheral.Speed 		= 400000,
		.I2C_SCL_GPIO_PORT 			= PORTA,
		.I2C_SDA_GPIO_PORT 			= PORTA,
		.I2C_SCL_GPIO_PIN 			= PIN2,
		.I2C_SDA_GPIO_PIN 			= PIN3
	},
};

I2C_DriverRetVal_e I2C_DriverInit(void);
I2C_DriverRetVal_e I2C_DriverDeInit(void);

I2C_DriverRetVal_e I2C_DriverWriteByte( I2C_DriverI2CPeripheralList_e I2C_peripheral, uint8_t deviceAddress_i, uint8_t deviceRegisterAddress_i, uint8_t data_i );
I2C_DriverRetVal_e I2C_DriverWriteData( I2C_DriverI2CPeripheralList_e I2C_peripheral, uint8_t deviceAddress_i, uint8_t deviceRegisterAddress_i, uint8_t* pData_i, uint16_t length_i );
I2C_DriverRetVal_e I2C_DriverReadByte(  I2C_DriverI2CPeripheralList_e I2C_peripheral, uint8_t deviceAddress_i, uint8_t deviceRegisterAddress_i, uint8_t* pData_o );
I2C_DriverRetVal_e I2C_DriverReadData(  I2C_DriverI2CPeripheralList_e I2C_peripheral, uint8_t deviceAddress_i, uint8_t deviceRegisterAddress_i, uint8_t* pData_o, uint16_t length_i );

