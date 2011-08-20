#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"

int main(void) {
	
	startup();
	for(;;){
		SetBit (PORT_LED_1, LED_1_NUMBER);
		_delay_ms (10000);
		ClearBit (PORT_LED_1, LED_1_NUMBER);
		_delay_ms (20000);
	}
}
	


void startup (void){

	SetBit (DDR_LED_1, LED_1_NUMBER);
	SetBit (DDR_LED_2, LED_2_NUMBER);
	SetBit (DDR_LED_3, LED_3_NUMBER);
	SetBit (DDR_LED_4, LED_4_NUMBER);

	ClearBit (DDR_SENSOR_1, SENSOR_1_NUMBER);
	ClearBit (DDR_SENSOR_2, SENSOR_2_NUMBER);


/*	DDRC |= ((1<<PC0) | (1<<PC1) | (1<<PC2));
	DDRC &= ~((1<<PC3) | (1<<PC4) | (1<<PC5));
	DDRD &=~ 1<<PD5;
	PORTD |= 1<<PD5;
*/
}
