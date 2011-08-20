#include	<avr/io.h>
#include	<avr/interrupt.h>

#include	"lib_sensores.h"


// Inicializacion de las entradas
void sensores_config(void){
	// Configura los pines como entradas
	PORT_SENS1 |= _BV(PIN_NUM_SENS1); 	
	PORT_SENS2 |= _BV(PIN_NUM_SENS2); 	
	PORT_SENS3 |= _BV(PIN_NUM_SENS3); 	
	
	DDR_SENS1 &=~ _BV(PIN_NUM_SENS1); 	
	DDR_SENS2 &=~ _BV(PIN_NUM_SENS2); 	
	DDR_SENS3 &=~ _BV(PIN_NUM_SENS3);
	
	// Inicializacion del timer de muestreo.
	// preescaler de 8
	// Con 8MHz=>255us
	//TCCR0 = (0<<CS01)|(1<<CS01)|(0<<CS00);
	
	// Habilita la interrupcion
	TIMSK |= (1<<TOIE0);	
}

void sensores_leer (void){
	
	// Cuando el sensor está sobre negro (PIN_SENSx & Sx) != 0
	// Cuando el sensor está sobre negro la entrada está en '1'.
	estado_sensores = ((PIN_SENS3 & S3)|(PIN_SENS2 & S2)|(PIN_SENS1 & S1));
//	estado_sensores = (~(PIN_SENS3|(~S3))) | (~(PIN_SENS2|(~S2))) | (~(PIN_SENS1|(~S1)));
	//estado_sensores = ((~(PIN_SENS2|(~S2))) | (~(PIN_SENS1|(~S1))));
}

// Inicia el muestreo.
// Luego de ejecutarla el timer desborda y toma
// la primer muestra.
inline void sensores_muestrear(void){
	// Pone el timer al borde del overflow.
	TCNT0 = 255;

	// Inicializacion del timer de muestreo.
	// preescaler de 8
	// Con 8MHz=>255us
	TCCR0 = (0<<CS01)|(0<<CS01)|(1<<CS00);
	// Estaba así, probando rapido lo cambiamos.
	//TCCR0 = (0<<CS01)|(1<<CS01)|(0<<CS00);
}

// Detiene el muestreo.
inline void sensores_detener(void){
	// Detiene el timer de muestreo.
	TCCR0 = (0<<CS01)|(0<<CS01)|(0<<CS00);
}

// Interrupcion de muestreo.
// Guarda el estado de los sensores en estado_sensores.
ISR(TIMER0_OVF_vect){
	sensores_leer();
}
