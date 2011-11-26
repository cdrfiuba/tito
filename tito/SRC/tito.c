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
 qu� eventos est�n permitidos para qu� estados,
 y cu�l es la funci�n encargada de manejar ese estado.
*/
typedef struct {
    uint16_t st;
    uint16_t ev;
    uint16_t st_new;
} tTransition;


/**
 funci�n principal
*/
int main() {

    uint16_t i = 0;

    // declaro "state" y "event" en vez de "estado" y "evento"
    // porque se distinguen m�s entre s�
    uint16_t state = ST_EN_LINEA;
    uint16_t event = EV_CUALQUIERA;

    // ac� se definen las transiciones de la fsm:
    // esencialmente esto ES la fsm
    // (los sensores se componen como:
    //  CURVA | S_IZQ | S_CEN | S_DER )
    static tTransition trans[] PROGMEM = {
        {ST_EN_LINEA, EV_SENSORES_BNNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_BBNN, ST_YENDOSE_POCO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_NNNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_EN_LINEA, EV_SENSORES_NNBB, ST_YENDOSE_POCO_POR_IZQUIERDA},

        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_BNNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NBBN, ST_VOLVIO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_BBNN, ST_VOLVIO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNNN, ST_AFUERA_POR_DERECHA},
        {ST_AFUERA_POR_DERECHA, EV_SENSORES_BNNN, ST_VOLVIENDO_POR_DERECHA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_BBNN, ST_VOLVIO_POR_DERECHA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NNNN, ST_AFUERA_POR_DERECHA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_BNNN, ST_YENDOSE_MUCHO_POR_DERECHA},

        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_VOLVIO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NNBB, ST_VOLVIO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NNNN, ST_AFUERA_POR_IZQUIERDA},
        {ST_AFUERA_POR_IZQUIERDA, EV_SENSORES_NNNB, ST_VOLVIENDO_POR_IZQUIERDA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NNBB, ST_VOLVIO_POR_IZQUIERDA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NNNN, ST_AFUERA_POR_IZQUIERDA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NNNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},

        {ST_MAX, EV_CUALQUIERA, ST_MAX}
    };
/*    static tTransition trans[] PROGMEM = {
        {ST_EN_LINEA, EV_SENSORES_BNNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_NBNN, ST_YENDOSE_POCO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_NNNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_EN_LINEA, EV_SENSORES_NNBN, ST_YENDOSE_POCO_POR_IZQUIERDA},

        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_BNNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},

        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},

        {ST_MAX, EV_CUALQUIERA, ST_MAX}
    };*/
    
    // obtengo el m�ximo de transiciones, buscando la �ltima
    uint16_t trans_count = 0;
    for (i = 0; ; i++) {
        trans_count = i;
        if (ST_MAX == pgm_read_byte_near(&(trans[i].st))) {
            break;
        }
    }

    // inicializaci�n motores, leds, bot�n
    startup();

    // ciclo principal del programa
    while (1) {
    
        PWM1_VEL(0);
        PWM2_VEL(COEFICIENTE_DERECHA * 0);

        // ciclos para esperar a que arranque cuando
        // se suelta el bot�n
        while (BOTON_NO_APRETADO);
        _delay_ms(50); //rebote bot�n
        mot1_sent(AD);
        mot2_sent(AD);
        state = ST_EN_LINEA;

        while (BOTON_APRETADO);
        _delay_ms(5); //rebote bot�n

        // inicializaci�n estado
        PWM1_VEL(10 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 10 * FACTOR);
        _delay_ms(80);
        PWM1_VEL(30 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 30 * FACTOR);
        _delay_ms(80);
        PWM1_VEL(70 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 70 * FACTOR);
        _delay_ms(80);
        PWM1_VEL(100 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 100 * FACTOR);
        
        // Ciclo de la fsm
        while (BOTON_NO_APRETADO) {// si se quiere que la fsm termine, se usa (state != ST_FIN)
        
            event = ESTADO_SENSORES; // obtiene el evento a procesar
            // cicla por todas las transiciones,
            // y busca la que coincida con el estado y evento actuales
            // si ninguna coincide, mantiene el estado actual
            for (i = 0; i < trans_count; i++) {
                if ((state == pgm_read_byte_near(&(trans[i].st))) && (event == pgm_read_byte_near(&(trans[i].ev)))) {
                    // maneja el estado actual
                    state = pgm_read_byte_near(&(trans[i].st_new));
                    switch (state) {
                        case ST_EN_LINEA:
                            PWM1_VEL(100 * FACTOR_ADELANTE);
                            PWM2_VEL(COEFICIENTE_DERECHA * 100 * FACTOR_ADELANTE);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;


                        case ST_YENDOSE_POCO_POR_DERECHA:
                            PWM1_VEL(75 * FACTOR);
                            PWM2_VEL(COEFICIENTE_DERECHA * 100 * FACTOR);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;

                        case ST_YENDOSE_MUCHO_POR_DERECHA:
                            PWM1_VEL(0 * FACTOR);
                            PWM2_VEL(COEFICIENTE_DERECHA * 80 * FACTOR);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;

                        case ST_AFUERA_POR_DERECHA:
                            PWM1_VEL(90 * FACTOR);
                            PWM2_VEL(COEFICIENTE_DERECHA * 100 * FACTOR);
                            mot1_sent(AT);
                            mot2_sent(AD);
                            break;


                        case ST_VOLVIENDO_POR_DERECHA:
                            PWM1_VEL(80 * FACTOR_ADELANTE);
                            PWM2_VEL(COEFICIENTE_DERECHA * 80 * FACTOR_ADELANTE);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;

                        case ST_VOLVIO_POR_DERECHA:
                            PWM1_VEL(90 * FACTOR_ADELANTE);
                            PWM2_VEL(COEFICIENTE_DERECHA * 90 * FACTOR_ADELANTE);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;



                        case ST_YENDOSE_POCO_POR_IZQUIERDA:
                            PWM1_VEL(100 * FACTOR);
                            PWM2_VEL(COEFICIENTE_DERECHA * 75 * FACTOR);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;

                        case ST_YENDOSE_MUCHO_POR_IZQUIERDA:
                            PWM1_VEL(80 * FACTOR);
                            PWM2_VEL(COEFICIENTE_DERECHA * 0 * FACTOR);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;

                        case ST_AFUERA_POR_IZQUIERDA:
                            PWM1_VEL(100 * FACTOR);
                            PWM2_VEL(COEFICIENTE_DERECHA * 90 * FACTOR);
                            mot1_sent(AD);
                            mot2_sent(AT);
                            break;


                        case ST_VOLVIENDO_POR_IZQUIERDA:
                            PWM1_VEL(80 * FACTOR_ADELANTE);
                            PWM2_VEL(COEFICIENTE_DERECHA * 80 * FACTOR_ADELANTE);
                            mot1_sent(AD);
                            mot2_sent(AD);
                            break;

                        case ST_VOLVIO_POR_IZQUIERDA:
                            PWM1_VEL(90 * FACTOR_ADELANTE);
                            PWM2_VEL(COEFICIENTE_DERECHA * 90 * FACTOR_ADELANTE);
                            mot1_sent(AD);
                            mot2_sent(AD);
                    }
                    
                    break;
                }
            }
            // Si llega a superar el l�mite real de transiciones, el for va a
            // leer cualquier cosa, y pueden pasar cosas raras.
            // Esto deber�a al menos dar un indicio de que pas� algo malo, y que
            // est� fallando el define len_pgm.
            //if (i > 2) {
            //    PWM1_VEL(0);
            //    PWM2_VEL(COEFICIENTE_DERECHA * 0);
            //    _delay_ms(2000);
            //}
        }

        // fin de tareas, para poder empezar de nuevo
        PWM1_VEL(0);
        PWM2_VEL(COEFICIENTE_DERECHA * 0);
        _delay_ms(50); //rebote bot�n

        while (BOTON_APRETADO);
        _delay_ms(50); //rebote bot�n

    }

    return 1;
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

    // bot�n
    ClearBit (DDR_BOTON, BOTON_NUMBER);
    SetBit (PORT_BOTON, BOTON_NUMBER);


    // PWM
    pwm_config();
    pwm_start();

    // pone el flag global para activar interrupciones
    sei();

    // establezco la direcci�n de los motores
    mot1_sent(AD);
    mot2_sent(AD);

}
