#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"
#include <avr/pgmspace.h>

void (*funciones[MAX_ESTADOS])();

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
 
static const uint_8 transiciones[MAX_ESTADOS][MAX_SENSORES] PROGMEM = {

                              /*NNNN NNNB NNBN NNBB NBNN NBNB NBBN NBBB BNNN BNNB BNBN BNBB BBNN BBNB BBBN BBBB*/
/* En Linea*/                   { ME,YMPI,}, 

/* Yendose Poco por Derecha*/   {, }, 
 /* Yendose Mucho por Derecha*/ {ST_YENDOSE_MUCHO_POR_DERECHA, },
/* Afuera por Derecha*/         {ST_AFUERA_POR_DERECHA, }, 
/* Volviendo por Derecha*/      {ST_VOLVIENDO_POR_DERECHA, }, 
/* Volvio por Derecha*/         {ST_VOLVIO_POR_DERECHA, }, 

/* Yendose Poco por Izquierda*/ {ST_YENDOSE_POCO_POR_IZQUIERDA, },
/* Yendose Mucho por Izquierda*/{ST_YENDOSE_MUCHO_POR_IZQUIERDA, }, 
/* Afuera por Izquierda*/       {ST_AFUERA_POR_IZQUIERDA, }, 
/* Volviendo por Izquierda*/    {ST_VOLVIENDO_POR_IZQUIERDA, }, 
/* Volvio por Izquierda*/       {ST_VOLVIO_POR_IZQUIERDA, }  
};

EL=0,
YPPD=1,
YMPD=2,
APD=3,
VEPD=4,
VOPD=5,
YPPI=6,
YMPI=7,
API=8,
VEPI=9,
VOPI=10,
ME=11

 
ST_EN_LINEA = 0,

ST_YENDOSE_POCO_POR_DERECHA = 1,
ST_YENDOSE_MUCHO_POR_DERECHA = 2,
ST_AFUERA_POR_DERECHA = 3,
ST_VOLVIENDO_POR_DERECHA = 4,
ST_VOLVIO_POR_DERECHA = 5,

ST_YENDOSE_POCO_POR_IZQUIERDA = 6,
ST_YENDOSE_MUCHO_POR_IZQUIERDA = 7,
ST_AFUERA_POR_IZQUIERDA = 8,
ST_VOLVIENDO_POR_IZQUIERDA = 9,
ST_VOLVIO_POR_IZQUIERDA = 10

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
    uint_8 estado_actual;
    uint_8 nuevo_estado;
    uint_8 estado_sensores;
    
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
        PWM2_VEL(COEFICIENTE_DERECHA * 0);

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON_NO_APRETADO);
        _delay_ms(50); //rebote botón
        estado_actual = ST_EN_LINEA;
        (*funciones[estado_actual])();
        

        while (BOTON_APRETADO);
        _delay_ms(5); //rebote botón

        // inicialización estado
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
        
        while (BOTON_NO_APRETADO) {
            estado_sensores = ESTADO_SENSORES; // obtiene el evento a procesar
            if ((nuevo_estado = pgm_read_byte_near(&(transiciones[estado_actual][estado_sensores]))) != MAX_ESTADOS) {
                estado_actual = nuevo_estado;
                (*funciones[estado_actual])();
            } else {
                continue;
            }
        }

        // fin de tareas, para poder empezar de nuevo
        PWM1_VEL(0);
        PWM2_VEL(COEFICIENTE_DERECHA * 0);
        _delay_ms(50); //rebote botón

        while (BOTON_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}
