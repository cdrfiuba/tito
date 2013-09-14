#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tito.h"
#include "lib/motores.h"
#include "lib/common.h"

void startup () {
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
    ClearBit (DDR_SENSOR_4, SENSOR_4_NUMBER);
    ClearBit (DDR_SENSOR_5, SENSOR_5_NUMBER);
    ClearBit (DDR_SENSOR_6, SENSOR_6_NUMBER);

    // botón1
    ClearBit (DDR_BOTON1, BOTON1_NUMBER);
    SetBit (PORT_BOTON1, BOTON1_NUMBER);

    // botón2
    ClearBit (DDR_BOTON2, BOTON2_NUMBER);
    SetBit (PORT_BOTON2, BOTON2_NUMBER);

    // configuración de PWMs en motores.h
    pwm_config();

    // pone el flag global para activar interrupciones
    sei();

}

typedef struct {
    int estado;
    int sensores;
    int estado_nuevo;
    //int tipo_estado; //RECTA o CURVA
} tTransition;

    
inline void manejar_estado(int estado) {
    switch (estado) {
        case ST_EN_LINEA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_EL);
            motor2_velocidad(VELOCIDAD_DERECHA_EL);
            break;

        case ST_YENDOSE_POCO_POR_DERECHA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_YPPD);
            motor2_velocidad(VELOCIDAD_DERECHA_YPPD);
            break;
        case ST_YENDOSE_MUCHO_POR_DERECHA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_YMPD);
            motor2_velocidad(VELOCIDAD_DERECHA_YMPD);
            break;
        case ST_AFUERA_POR_DERECHA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_APD);
            motor2_velocidad(VELOCIDAD_DERECHA_APD);
            break;
        case ST_VOLVIENDO_POR_DERECHA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_VEPD);
            motor2_velocidad(VELOCIDAD_DERECHA_VEPD);
            break;
        case ST_VOLVIO_POR_DERECHA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_VOPD);
            motor2_velocidad(VELOCIDAD_DERECHA_VOPD);
            break;

        case ST_YENDOSE_POCO_POR_IZQUIERDA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_YPPI);
            motor2_velocidad(VELOCIDAD_DERECHA_YPPI);
            break;
        case ST_YENDOSE_MUCHO_POR_IZQUIERDA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_YMPI);
            motor2_velocidad(VELOCIDAD_DERECHA_YMPI);
            break;
        case ST_AFUERA_POR_IZQUIERDA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_API);
            motor2_velocidad(VELOCIDAD_DERECHA_API);
            break;
        case ST_VOLVIENDO_POR_IZQUIERDA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_VEPI);
            motor2_velocidad(VELOCIDAD_DERECHA_VEPI);
            break;
        case ST_VOLVIO_POR_IZQUIERDA:
            motor1_velocidad(VELOCIDAD_IZQUIERDA_VOPI);
            motor2_velocidad(VELOCIDAD_DERECHA_VOPI);
            break;
    }
}
    
/**
 función principal
*/
int main() {
    int i = 0;
    int trans_count = 0;
    int estado_actual = ST_EN_LINEA;
    int lectura_sensores = EV_CUALQUIERA;
    
    startup();
    /*while (1) {
        if (SENSOR_IZQUIERDA_CENTRO)
	        SetBit (PORT_LED_1, LED_1_NUMBER);
        else
            ClearBit (PORT_LED_1, LED_1_NUMBER);
        if (SENSOR_IZQUIERDA_AFUERA)
	        SetBit (PORT_LED_2, LED_2_NUMBER);
        else
            ClearBit (PORT_LED_2, LED_2_NUMBER);
        if (SENSOR_DERECHA_AFUERA)
	        SetBit (PORT_LED_3, LED_3_NUMBER);
        else
            ClearBit (PORT_LED_3, LED_3_NUMBER);
        if (SENSOR_DERECHA_CENTRO)
	        SetBit (PORT_LED_4, LED_4_NUMBER);
        else
            ClearBit (PORT_LED_4, LED_4_NUMBER);
    }*/
    
    while (1) {
        SetBit (PORT_LED_1, LED_1_NUMBER);
        
        OCR0A = 0;
        OCR0B = 0;
        _delay_ms(500);

        ClearBit (PORT_LED_1, LED_1_NUMBER);

        OCR0A = 128;
        OCR0B = 128;
        _delay_ms(500);
    }
    

    // acá se definen las transiciones de la fsm:
    // esencialmente esto ES la fsm
    tTransition transiciones[] = {
        {ST_EN_LINEA, EV_SENSORES_NNNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_EN_LINEA, EV_SENSORES_NNBN, ST_YENDOSE_POCO_POR_IZQUIERDA},
        {ST_EN_LINEA, EV_SENSORES_NNBB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_EN_LINEA, EV_SENSORES_NBNN, ST_YENDOSE_POCO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_BNNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_BBNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        //{ST_EN_LINEA, EV_CUALQUIREA, ST_MAX_ESTADOS}, // para determinar que no hay más posibilidades en este estado

        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NNNN, ST_AFUERA_POR_DERECHA},
        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NNBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_BNNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_BBNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNNN, ST_AFUERA_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNNB, ST_VOLVIO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNBN, ST_VOLVIO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNBB, ST_VOLVIO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NBNN, ST_EN_LINEA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NBBN, ST_VOLVIO_POR_DERECHA},
        {ST_AFUERA_POR_DERECHA, EV_SENSORES_BNNN, ST_VOLVIENDO_POR_DERECHA},
        {ST_AFUERA_POR_DERECHA, EV_SENSORES_BBNN, ST_VOLVIENDO_POR_DERECHA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NNNN, ST_AFUERA_POR_DERECHA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NNBN, ST_VOLVIO_POR_DERECHA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NBNN, ST_EN_LINEA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_NNBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_NBNN, ST_EN_LINEA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_BBNN, ST_YENDOSE_POCO_POR_DERECHA},

        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNNN, ST_AFUERA_POR_IZQUIERDA},
        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NBNN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNBB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NNNN, ST_AFUERA_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_BNNN, ST_VOLVIO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NBNN, ST_VOLVIO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_BBNN, ST_VOLVIO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NNBN, ST_EN_LINEA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_VOLVIO_POR_IZQUIERDA},
        {ST_AFUERA_POR_IZQUIERDA, EV_SENSORES_NNNB, ST_VOLVIENDO_POR_IZQUIERDA},
        {ST_AFUERA_POR_IZQUIERDA, EV_SENSORES_NNBB, ST_VOLVIENDO_POR_IZQUIERDA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NNNN, ST_AFUERA_POR_IZQUIERDA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBNN, ST_VOLVIO_POR_IZQUIERDA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NNBN, ST_EN_LINEA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NBNN, ST_EN_LINEA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NNBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NBBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NNBB, ST_YENDOSE_POCO_POR_IZQUIERDA},   
        
        {ST_MAX_ESTADOS, EV_CUALQUIERA, ST_MAX_ESTADOS} // transición máxima
    };

        
    for (i = 0; ; i++) {
        trans_count = i + 1;
        if (ST_MAX_ESTADOS == transiciones[i].estado) {
            break;
        }
    }
    
    
    while (1) {
       motor1_velocidad(0);
       motor2_velocidad(0);

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON1_NO_APRETADO);
        _delay_ms(50); //rebote botón
        

        while (BOTON1_APRETADO);
        _delay_ms(5); //rebote botón

        // aceleración inicial gradual
       motor1_velocidad(50);
       motor2_velocidad(50);
        _delay_ms(50);
        
        // inicialización estado
        estado_actual = ST_EN_LINEA;
        
        while (BOTON1_NO_APRETADO) {
            lectura_sensores = ESTADO_SENSORES;
            /* // relectura de sensores
            while(1) {
                lectura_sensores_nuevo = ESTADO_SENSORES;
                if (lectura_sensores_nuevo == lectura_sensores) {
                    break;
                }
                lectura_sensores = lectura_sensores_nuevo;
            }*/

            // cicla por todas las transiciones, y busca la que coincida con
            // el estado y evento actuales
            for (i = 0; i < trans_count; i++) {
                if ((estado_actual == transiciones[i].estado) && (lectura_sensores == transiciones[i].sensores)) {
                    estado_actual = transiciones[i].estado_nuevo;
                    manejar_estado(estado_actual);
                    break;
                }
            }
        }

        // fin de tareas, para poder empezar de nuevo
       motor1_velocidad(0);
       motor2_velocidad(0);
        _delay_ms(50); //rebote botón

        while (BOTON1_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}

