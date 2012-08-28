#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"
#include <avr/pgmspace.h>

void (*funciones[ST_MAX_ESTADOS])();

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

/*Tabla de Posibles transiciones*/
static const int transiciones[ST_MAX_ESTADOS][EV_MAX_SENSORES] PROGMEM = {
                              /*NNNN NNNB NNBN NNBB NBNN NBNB NBBN NBBB BNNN BNNB BNBN BNBB BBNN BBNB BBBN BBBB*/
/* En Linea*/                   { ME,YMPI,YPPI,YMPI,YPPD,  ME,  ME,  ME,YMPD,  ME,  ME,  ME,YMPD,  ME,  ME,  ME}, 

/* Yendose Poco por Derecha*/   {APD,  ME,  EL,  ME,  ME,  ME,  EL,  ME,YMPD,  ME,  ME,  ME,YMPD,  ME,  ME,  ME}, 
/* Yendose Mucho por Derecha*/  {APD,VOPD,VOPD,VOPD,  EL,  ME,VOPD,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME},
/* Afuera por Derecha*/         { ME,  ME,  ME,  ME,VEPD,  ME,  ME,  ME,VEPD,  ME,  ME,  ME,VEPD,  ME,  ME,  ME}, 
/* Volviendo por Derecha*/      { ME,  ME,VOPD,  ME,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volvio por Derecha*/         { ME,  ME,  EL,  ME,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,YPPD,  ME,  ME,  ME}, 

/* Yendose Poco por Izquierda*/ {API,YMPI,  ME,YMPI,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME},
/* Yendose Mucho por Izquierda*/{API,  ME,  EL,  ME,VOPI,  ME,VOPI,  ME,VOPI,  ME,  ME,  ME,VOPI,  ME,  ME,  ME}, 
/* Afuera por Izquierda*/       { ME,VEPI,VEPI,VEPI,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volviendo por Izquierda*/    { ME,  ME,  EL,  ME,VOPI,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volvio por Izquierda*/       { ME,  ME,  EL,YPPI,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}  
};


void st_en_linea () {
    PWM1_VEL(100);
    PWM2_VEL(100);
    mot1_sent(AD);
    mot2_sent(AD);
};

void st_yendose_poco_por_derecha () {
    PWM1_VEL(60);
    PWM2_VEL(100);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_yendose_mucho_por_derecha () {
    PWM1_VEL(0);
    PWM2_VEL(100);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_afuera_por_derecha () {
    PWM1_VEL(30);
    PWM2_VEL(100);
    mot1_sent(AT);
    mot2_sent(AD);
};
void st_volviendo_por_derecha () {
    PWM1_VEL(100);
    PWM2_VEL(100);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_volvio_por_derecha () {
    PWM1_VEL(100);
    PWM2_VEL(100);
    mot1_sent(AD);
    mot2_sent(AD);
};

void st_yendose_poco_por_izquierda () {
    PWM1_VEL(100);
    PWM2_VEL(60);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_yendose_mucho_por_izquierda () {
    PWM1_VEL(100);
    PWM2_VEL(0);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_afuera_por_izquierda () {
    PWM1_VEL(100);
    PWM2_VEL(30);
    mot1_sent(AD);
    mot2_sent(AT);
};
void st_volviendo_por_izquierda () {
    PWM1_VEL(100);
    PWM2_VEL(100);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_volvio_por_izquierda () {
    PWM1_VEL(100);
    PWM2_VEL(100);
    mot1_sent(AD);
    mot2_sent(AD);
};

/**
 función principal
*/
int main() {
    int estado_actual;
    int nuevo_estado;
    int estado_sensores;
    
    startup();
    
    funciones[ST_EN_LINEA] = st_en_linea;
    
    funciones[ST_YENDOSE_POCO_POR_DERECHA] = st_yendose_poco_por_derecha;
    funciones[ST_YENDOSE_MUCHO_POR_DERECHA] = st_yendose_mucho_por_derecha;
    funciones[ST_AFUERA_POR_DERECHA] = st_afuera_por_derecha;
    funciones[ST_VOLVIENDO_POR_DERECHA] = st_volviendo_por_derecha;
    funciones[ST_VOLVIO_POR_DERECHA] = st_volvio_por_derecha;

    funciones[ST_YENDOSE_POCO_POR_IZQUIERDA] = st_yendose_poco_por_izquierda;
    funciones[ST_YENDOSE_MUCHO_POR_IZQUIERDA] = st_yendose_mucho_por_izquierda;
    funciones[ST_AFUERA_POR_IZQUIERDA] = st_afuera_por_izquierda;
    funciones[ST_VOLVIENDO_POR_IZQUIERDA] = st_volviendo_por_izquierda;
    funciones[ST_VOLVIO_POR_IZQUIERDA] = st_volvio_por_izquierda;
    
    estado_actual = ST_EN_LINEA;
    (*funciones[estado_actual])();
    
    while (1) {
        PWM1_VEL(0);
        PWM2_VEL(0);

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON_NO_APRETADO);
        _delay_ms(50); //rebote botón
        estado_actual = ST_EN_LINEA;
        (*funciones[estado_actual])();
        

        while (BOTON_APRETADO);
        _delay_ms(5); //rebote botón

        // inicialización estado
        PWM1_VEL(COEFICIENTE_IZQUIERDA * 10 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 10 * FACTOR);
        _delay_ms(80);
        PWM1_VEL(COEFICIENTE_IZQUIERDA * 30 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 30 * FACTOR);
        _delay_ms(80);
        PWM1_VEL(COEFICIENTE_IZQUIERDA * 70 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 70 * FACTOR);
        _delay_ms(80);
        PWM1_VEL(COEFICIENTE_IZQUIERDA * 100 * FACTOR);
        PWM2_VEL(COEFICIENTE_DERECHA * 100 * FACTOR);
        
        while (BOTON_NO_APRETADO) {
            estado_sensores = ESTADO_SENSORES; // obtiene el evento a procesar
            if ((nuevo_estado = pgm_read_byte_near(&(transiciones[estado_actual][estado_sensores]))) != ST_MAX_ESTADOS) {
                estado_actual = nuevo_estado;
                (*funciones[estado_actual])();
            } else {
                continue;
            }
        }

        // fin de tareas, para poder empezar de nuevo
        PWM1_VEL(0);
        PWM2_VEL(0);
        _delay_ms(50); //rebote botón

        while (BOTON_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}
