#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"

int main(void) 
{
	
	startup();
	pwm_start();
	
	mot1_sent(AD);
	PWM1_VEL(100);
	mot2_sent(AD);
	PWM2_VEL(100);

	for(;;)
	{
		if (IsBitSet(PIN_SENSOR_1, SENSOR_1_NUMBER)){
			PWM1_VEL(60);
			PWM2_VEL(100);
		}
		else if (IsBitSet(PIN_SENSOR_1, SENSOR_1_NUMBER)){
			PWM1_VEL(100);
			PWM2_VEL(60);
		
		}
		else {
			PWM1_VEL(100);
			PWM2_VEL(100);

		}
	}
}
	


void startup (void)
{
	SetBit (DDR_LED_1, LED_1_NUMBER);
	SetBit (DDR_LED_2, LED_2_NUMBER);
	SetBit (DDR_LED_3, LED_3_NUMBER);
	SetBit (DDR_LED_4, LED_4_NUMBER);

	ClearBit (DDR_SENSOR_1, SENSOR_1_NUMBER);
	ClearBit (DDR_SENSOR_2, SENSOR_2_NUMBER);
	ClearBit (DDR_SENSOR_3, SENSOR_3_NUMBER);
	ClearBit (DDR_SENSOR_CURVA, SENSOR_CURVA_NUMBER);
	pwm_config();
	sei();	

}
