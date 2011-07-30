#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"

int main(void) {
	
	startup();
/*    for (;;) {
		if (IsBitSet(PORT_SENSOR_1, SENSOR_1_NUMBER)) {
			MoverIzquierda();
		} else if (IsBitSet(PORT_SENSOR_2, SENSOR_2_NUMBER)) {
			MoverDerecha();
		} else {
			MoverAdelante();
		}
    }
*/
	for(;;){
		MoverAdelante();
	}
}

void MoverIzquierda (void) {
	SetBit (PORT_IN_1_A, IN_1_A_NUMBER);
	ClearBit (PORT_IN_2_A, IN_2_A_NUMBER);
	ClearBit (PORT_IN_3_B, IN_3_B_NUMBER);
	ClearBit (PORT_IN_4_B, IN_4_B_NUMBER);
}	
void MoverDerecha (void) {
	ClearBit (PORT_IN_1_A, IN_1_A_NUMBER);
	ClearBit (PORT_IN_2_A, IN_2_A_NUMBER);
	ClearBit (PORT_IN_3_B, IN_3_B_NUMBER);
	SetBit (PORT_IN_4_B, IN_4_B_NUMBER);
}	
void MoverAdelante (void) {
	SetBit (PORT_IN_1_A, IN_1_A_NUMBER);
	SetBit (PORT_IN_2_A, IN_2_A_NUMBER);
	SetBit (PORT_IN_3_B, IN_3_B_NUMBER);
	SetBit (PORT_IN_4_B, IN_4_B_NUMBER);
}	


void startup (void){

	SetBit (DDR_LED_1, LED_1_NUMBER);
	SetBit (DDR_LED_2, LED_2_NUMBER);
	SetBit (DDR_LED_3, LED_3_NUMBER);
	SetBit (DDR_LED_4, LED_4_NUMBER);

	SetBit (DDR_ENABLE_A, ENABLE_A_NUMBER);
	SetBit (DDR_ENABLE_B, ENABLE_B_NUMBER);

	SetBit (DDR_IN_1_A, IN_1_A_NUMBER);
	SetBit (DDR_IN_2_A, IN_2_A_NUMBER);
	SetBit (DDR_IN_3_B, IN_3_B_NUMBER);
	SetBit (DDR_IN_4_B, IN_4_B_NUMBER);

	ClearBit (DDR_SENSOR_1, SENSOR_1_NUMBER);
	ClearBit (DDR_SENSOR_2, SENSOR_2_NUMBER);

	// habilita prender los motores
	SetBit (PORT_ENABLE_A, ENABLE_A_NUMBER);
	SetBit (PORT_ENABLE_B, ENABLE_B_NUMBER);

/*	DDRC |= ((1<<PC0) | (1<<PC1) | (1<<PC2));
	DDRC &= ~((1<<PC3) | (1<<PC4) | (1<<PC5));
	DDRD &=~ 1<<PD5;
	PORTD |= 1<<PD5;
*/
}
