#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"

int main(void) {

	// llamo a inicializar, puertos y PWM
	startup();

	// establezco la direcci�n de los motores
	mot1_sent(AD);
	mot2_sent(AD);

	// bucle principal,
	// hago polling del estado de los sensores,
	// (en un orden espec�fico)
	// y act�o en consecuencia
	for(;;)	{
		// si est�n los sensores de la izquierda y de la derecha,
		// entonces asumo que estoy cruzando una l�nea horizontal,
		// por lo que no cambio nada
		if (SENSOR_IZQUIERDA && SENSOR_DERECHA) {
			// no hacer nada
		// si est� el sensor de la izquierda,
		// entonces asumo que estoy desviado hacia la derecha,
		// por lo que debo girar hacia la izquierda
		} else if (SENSOR_IZQUIERDA) {
			PWM1_VEL(0);
			PWM2_VEL(100);
		// si est� el sensor de la derecha,
		// entonces asumo que estoy desviado hacia la izquierda,
		// por lo que debo girar hacia la derecha
		} else if (SENSOR_DERECHA) {
			PWM1_VEL(100);
			PWM2_VEL(0);
		// si est� el sensor del medio,
		// entonces asumo que estoy yendo bien,
		// por lo que avanzo hacia adelante
		} else if (SENSOR_MEDIO) {
			PWM1_VEL(100);
			PWM2_VEL(100);
		}
	}


}



void startup (void) {
// setear puertos de lectura o escritura,
// seg�n corresponda

	// leds
	SetBit (DDR_LED_1, LED_1_NUMBER);
	SetBit (DDR_LED_2, LED_2_NUMBER);
	SetBit (DDR_LED_3, LED_3_NUMBER);
	SetBit (DDR_LED_4, LED_4_NUMBER);

	// sensores
	ClearBit (DDR_SENSOR_1, SENSOR_1_NUMBER);
	ClearBit (DDR_SENSOR_2, SENSOR_2_NUMBER);
	ClearBit (DDR_SENSOR_3, SENSOR_3_NUMBER);
	ClearBit (DDR_SENSOR_CURVA, SENSOR_CURVA_NUMBER);

	// PWM
	pwm_config();
	pwm_start();

	// pone el flag global para activar interrupciones
	sei();

}
