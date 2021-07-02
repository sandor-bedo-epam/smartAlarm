
/**
* PWM driver description
*/
typedef enum {
	pwmDriverRetVal_OK = 0,
	pwmDriverRetVal_NOK,
	pwmDriverRetVal_End
} pwmDriverRetVal_e;

typedef enum {
	pwmDriverPinPWMStatus_Enabled = 0,
	pwmDriverPinPWMStatus_Disabled,
	pwmDriverPinPWMStatus_End
} pwmDriverPinPWMStatus_e;

typedef struct {
	uint32_t 				pwmDriverPin;
	uint32_t 				pwmDriverFrequency;
	uint8_t  				pwmDriverDuty;			/* in percent 0-100 */
	pwmDriverPinPWMStatus_e pwmDriverPinPWMStatus;
} pwmDriverPinParameters_s;

typedef enum {
	pwmDriver_Pin0 = 0,
	pwmDriver_Pin1,
	pwmDriver_Pin2,
	pwmDriver_Pin3,
	pwmDriver_Pin4,
	pwmDriver_Pin_End
} pwmDriverPinList_e;

pwmDriverPinParameters_s smartAlarmPWMPinList[ pwmDriver_Pin_End ] = {
	{
		.pwmDriverPin = 0,
		.pwmDriverFrequency = 1000,
		.pwmDriverDuty = 50,
		.pwmDriverPinPWMStatus = pwmDriverPinPWMStatus_Disabled
	},
	
}

pwmDriverRetVal_e 			PWM_DriverInit			  ( void );
pwmDriverRetVal_e 			PWM_DriverDeInit		  ( void );
static pwmDriverRetVal_e 	PWM_DriverInitPin		  ( pwmDriverPinParameters_s pinParameters_i );
pwmDriverRetVal_e 			PWM_DriverSetDuty		  ( pwmDriverPinParameters_s pinParameters_i );
pwmDriverRetVal_e 			PWM_DriverSetFrequency    ( pwmDriverPinParameters_s pinParameters_i );
pwmDriverRetVal_e 			PWM_DriverGetParameters   ( pwmDriverPinList_e pwmDriverPin_i );
pwmDriverRetVal_e			PWM_DriverEnablePWM		  ( pwmDriverPinParameters_s pinParameters_i );
pwmDriverRetVal_e			PWM_DriverDisablePWM	  ( pwmDriverPinParameters_s pinParameters_i );
pwmDriverRetVal_e			PWM_DriverGetPinPWMStatus ( pwmDriverPinParameters_s* pPinParameters_i );
