#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"
#include <avr/pgmspace.h>


/**
 estructura para transiciones:
 determina el flujo de la fsm, es decir,
 qué eventos están permitidos para qué estados,
 y cuál es la función encargada de manejar ese estado.
*/
typedef struct {
    uint16_t st;
    uint16_t ev;
    uint16_t st_new;//(*fn)(void *);
} tTransition;

/**
 handlers de eventos
 */
uint16_t manejar_estado(uint16_t estado) {
	#define FACTOR 1 // coeficiente de disminuición de velocidad
	switch (estado) {
		case ST_EN_LINEA:
			PWM1_VEL(100 * FACTOR);
			PWM2_VEL(100 * FACTOR);
			mot1_sent(AD);
			mot2_sent(AD);
			break;
	

		case ST_YENDOSE_POCO_POR_DERECHA:
			PWM1_VEL(75 * FACTOR);
			PWM2_VEL(100 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_YENDOSE_MUCHO_POR_DERECHA:
			PWM1_VEL(35 * FACTOR);
			PWM2_VEL(100 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_AFUERA_POR_DERECHA:
			PWM1_VEL(0 * FACTOR);
			PWM2_VEL(100 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_VOLVIENDO_POR_DERECHA:
			PWM1_VEL(100 * FACTOR);
			PWM2_VEL(85 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_VOLVIO_POR_DERECHA:
			PWM1_VEL(100 * FACTOR);
			PWM2_VEL(95 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	

		case ST_YENDOSE_POCO_POR_IZQUIERDA:
			PWM1_VEL(100 * FACTOR);
			PWM2_VEL(75 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_YENDOSE_MUCHO_POR_IZQUIERDA:
			PWM1_VEL(100 * FACTOR);
			PWM2_VEL(35 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_AFUERA_POR_IZQUIERDA:
			PWM1_VEL(100 * FACTOR);
			PWM2_VEL(0 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_VOLVIENDO_POR_IZQUIERDA:
			PWM1_VEL(85 * FACTOR);
			PWM2_VEL(100 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;
	
		case ST_VOLVIO_POR_IZQUIERDA:
			PWM1_VEL(95 * FACTOR);
			PWM2_VEL(100 * FACTOR);
			mot1_sent(AT);
			mot2_sent(AT);
			break;

			// esto permite que cuando no existe una transición
			// explícita, el estado no cambie
			
	}
	return estado;
}

/**
 Función principal para la fsm, se encarga de devolver
 el evento que corresponde.
 Si se quisiera implementar una cola de eventos,
 esta función sería la responsable de manejarla.
*/
uint16_t obtener_evento(void) {
	return ((SENSOR_DERECHA << 2) | (SENSOR_CENTRO << 1) | (SENSOR_IZQUIERDA));
}

/**
 función principal
*/
int main() {

	uint16_t i = 0;

	// declaro "state" y "event" en vez de "estado" y "evento"
	// porque se distinguen más entre sí
	uint16_t state = ST_EN_LINEA;
	uint16_t event = EV_CUALQUIERA;

	// acá se definen las transiciones de la fsm:
	// esencialmente esto ES la fsm
	static tTransition trans[] PROGMEM = {
		{ST_EN_LINEA, EV_SENSORES_BNN, ST_YENDOSE_MUCHO_POR_DERECHA},
		{ST_EN_LINEA, EV_SENSORES_BBN, ST_YENDOSE_POCO_POR_DERECHA},
		{ST_EN_LINEA, EV_SENSORES_NNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
		{ST_EN_LINEA, EV_SENSORES_NBB, ST_YENDOSE_POCO_POR_IZQUIERDA},

		{ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NBN, ST_EN_LINEA},
		{ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_BNN, ST_YENDOSE_MUCHO_POR_DERECHA},
		{ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_BBN, ST_VOLVIO_POR_DERECHA},
		{ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNN, ST_AFUERA_POR_DERECHA},
		{ST_AFUERA_POR_DERECHA, EV_SENSORES_BNN, ST_VOLVIENDO_POR_DERECHA},
		{ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NBN, ST_EN_LINEA},
		{ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_BBN, ST_VOLVIO_POR_DERECHA},
		{ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NNN, ST_AFUERA_POR_DERECHA},
		{ST_VOLVIO_POR_DERECHA, EV_SENSORES_NBN, ST_EN_LINEA},
		{ST_VOLVIO_POR_DERECHA, EV_SENSORES_BNN, ST_YENDOSE_MUCHO_POR_DERECHA},

		{ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NBN, ST_EN_LINEA},
		{ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
		{ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NBB, ST_VOLVIO_POR_IZQUIERDA},
		{ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NNN, ST_AFUERA_POR_IZQUIERDA},
		{ST_AFUERA_POR_IZQUIERDA, EV_SENSORES_NNB, ST_VOLVIENDO_POR_IZQUIERDA},
		{ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBN, ST_EN_LINEA},
		{ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBB, ST_VOLVIO_POR_IZQUIERDA},
		{ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NNN, ST_AFUERA_POR_IZQUIERDA},
		{ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NBN, ST_EN_LINEA},
		{ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},

		{ST_CUALQUIERA, EV_CUALQUIERA, ST_CUALQUIERA} // transición default
	};
	#define TRANS_COUNT 50 //(sizeof(trans)/sizeof(*trans))

	startup();

	// ciclo principal del programa
	while (1) {

		/*while (1) {
			PWM1_VEL(100);
			PWM2_VEL(100);
		}*/

        PWM1_VEL(0);
        PWM2_VEL(0);

		// ciclos para esperar a que arranque cuando
		// se suelta el botón
		while (BOTON_NO_APRETADO);
		_delay_ms(50); //rebote botón
		while (BOTON_APRETADO);
		_delay_ms(5); //rebote botón

		state = ST_EN_LINEA;
		PWM1_VEL(100);
		PWM2_VEL(100);
		_delay_ms(1500);
		// Ciclo de la fsm
		while (BOTON_NO_APRETADO) {// si se quiere que la fsm termine, se usa (state != ST_FIN)
			event = obtener_evento();
			if (event == 0){
				mot1_sent(AD);
				mot2_sent(AD);			
				PWM1_VEL(100);			
				PWM2_VEL(100);
			}
			if (event == 0){
				mot1_sent(AD);
				mot2_sent(AD);			
				PWM1_VEL(100);			
				PWM2_VEL(100);
			}
			if (event == 1){
				mot1_sent(AD);
				mot2_sent(AD);			
				PWM1_VEL(100);			
				PWM2_VEL(0);
			}
			if (event == 2){
				mot1_sent(AD);
				mot2_sent(AD);			
				PWM1_VEL(0);			
				PWM2_VEL(100);
			}
			if (event == 3){
				mot1_sent(AD);
				mot2_sent(AD);			
				PWM1_VEL(0);			
				PWM2_VEL(0);
			}
			if (event == 4){
				mot1_sent(AD);
				mot2_sent(AT);			
				PWM1_VEL(100);			
				PWM2_VEL(100);
			}
			if (event == 5){
				mot1_sent(AD);
				mot2_sent(AT);			
				PWM1_VEL(100);			
				PWM2_VEL(0);
			}
			if (event == 6){
				mot1_sent(AD);
				mot2_sent(AT);			
				PWM1_VEL(0);			
				PWM2_VEL(100);
			}
			if (event == 7){
				mot1_sent(AT);
				mot2_sent(AT);			
				PWM1_VEL(100);			
				PWM2_VEL(100);
			}

/*			event = obtener_evento(); // obtiene el evento a procesar
			// cicla por todas las transiciones, y busca la que coincida con el
			// estado y evento actuales
			for (i = 0; i < TRANS_COUNT; i++) {
				if ((state == pgm_read_byte_near(&(trans[i].st))) || (ST_CUALQUIERA == pgm_read_byte_near(&(trans[i].st)))) {
					if ((event == pgm_read_byte_near(&(trans[i].ev))) || (EV_CUALQUIERA == pgm_read_byte_near(&(trans[i].ev)))) {
						// llama a la función encargada de 
						// manejar el estado actual y devolver el nuevo estado
						state = manejar_estado(pgm_read_byte_near(&(trans[i].st_new)));
						break;
					}
				}
			}
			if (i == TRANS_COUNT) {
				PWM1_VEL(0);
				PWM2_VEL(0);
				_delay_ms(500);
			}
*/
		}

		// fin de tareas, para poder empezar de nuevo
        PWM1_VEL(0);
        PWM2_VEL(0);
		_delay_ms(50); //rebote botón

        while (BOTON_APRETADO);
		_delay_ms(50); //rebote botón

	}

	return 1;
}

void startup (void) {
// setear puertos de lectura o escritura,
// según corresponda

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

	// botón
	ClearBit (DDR_BOTON, BOTON_NUMBER);
	SetBit (PORT_BOTON, BOTON_NUMBER);


	// PWM
	pwm_config();
	pwm_start();

	// pone el flag global para activar interrupciones
	sei();

	// establezco la dirección de los motores
	mot1_sent(AD);
	mot2_sent(AD);

}

