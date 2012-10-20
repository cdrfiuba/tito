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
/* Volviendo por Derecha*/      {APD,  ME,VOPD,  ME,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volvio por Derecha*/         { ME,  ME,  EL,  ME,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,YPPD,  ME,  ME,  ME}, 

/* Yendose Poco por Izquierda*/ {API,YMPI,  ME,YMPI,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME},
/* Yendose Mucho por Izquierda*/{API,  ME,  EL,  ME,VOPI,  ME,VOPI,  ME,VOPI,  ME,  ME,  ME,VOPI,  ME,  ME,  ME}, 
/* Afuera por Izquierda*/       { ME,VEPI,VEPI,VEPI,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volviendo por Izquierda*/    {API,  ME,  EL,  ME,VOPI,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volvio por Izquierda*/       { ME,  ME,  EL,YPPI,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}  
};

/*
void st_en_linea () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA * 100);
    PWM2_VEL(COEFICIENTE_DERECHA   * 100);
    mot1_sent(AD);
    mot2_sent(AD);
};

void st_yendose_poco_por_derecha () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA * 100);
    PWM2_VEL(COEFICIENTE_DERECHA  *   70);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_yendose_mucho_por_derecha () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA *  20);
    PWM2_VEL(COEFICIENTE_DERECHA *   100);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_afuera_por_derecha () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA *  35);
    PWM2_VEL(COEFICIENTE_DERECHA  *  100);
    mot1_sent(AT);
    mot2_sent(AD);
};
void st_volviendo_por_derecha () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA *  40);
    PWM2_VEL(COEFICIENTE_DERECHA   * 100);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_volvio_por_derecha () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA * 100);
    PWM2_VEL(COEFICIENTE_DERECHA   *  80);
    mot1_sent(AD);
    mot2_sent(AD);
};

void st_yendose_poco_por_izquierda () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA *  70);
    PWM2_VEL(COEFICIENTE_DERECHA   * 100);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_yendose_mucho_por_izquierda () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA * 100);
    PWM2_VEL(COEFICIENTE_DERECHA   *  20);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_afuera_por_izquierda () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA *  100);
    PWM2_VEL(COEFICIENTE_DERECHA   * 35);
    mot1_sent(AD);
    mot2_sent(AT);
};
void st_volviendo_por_izquierda () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA * 100);
    PWM2_VEL(COEFICIENTE_DERECHA   *  40);
    mot1_sent(AD);
    mot2_sent(AD);
};
void st_volvio_por_izquierda () {
    PWM1_VEL(COEFICIENTE_IZQUIERDA *  80);
    PWM2_VEL(COEFICIENTE_DERECHA   * 100);
    mot1_sent(AD);
    mot2_sent(AD);
};
*/
/**
 función principal
*/
int main() {
    //int estado_actual;
    //int nuevo_estado;
    unsigned int estado_sensores;
    int proportional = 0;
    int last_proportional = 0;
    int derivative = 0;
    int integral = 0;
    int power_difference = 0;
    const int max_power = 10;
    
    startup();
    /*
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
    */
    while (1) {
        PWM1_VEL(0);
        PWM2_VEL(0);

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON_NO_APRETADO);
        _delay_ms(50); //rebote botón
        

        while (BOTON_APRETADO);
        _delay_ms(5); //rebote botón

        // aceleración inicial gradual
        PWM1_VEL(5);
        PWM2_VEL(5);
        _delay_ms(50);

        PWM1_VEL(10);
        PWM2_VEL(10);
        _delay_ms(50);
        
        // inicialización estado
        //estado_actual = ST_EN_LINEA;
        //(*funciones[estado_actual])();
        
        while (BOTON_NO_APRETADO) {
            // inspirado en http://www.pololu.com/docs/0J21/7.c
        
            // sólo actualizo los sensores si hay al menos un sensor prendido;
            // esto tiene el efecto de "recordar" la última posición de la línea,
            // dado que si pasa de b1000 a b0000, sigue devolviendo b1000, asumiendo que la línea está a la izquierda,
            // y si pasa de b0001 a b0000, sigue devolviendo b0001, asumiendo que la línea está a la derecha.
            if (ESTADO_SENSORES > 0) {
                estado_sensores = (SENSOR_CURVA * 30 + SENSOR_IZQUIERDA * 20 + SENSOR_CENTRO * 10 + SENSOR_DERECHA * 00) / 
                        (SENSOR_CURVA + SENSOR_IZQUIERDA + SENSOR_CENTRO + SENSOR_DERECHA);
            }
            // 0b1000 --> d08 --> 30 / 1 = 30
            // 0b1100 --> d12 --> 50 / 2 = 25
            // 0b0110 --> d06 --> 30 / 2 = 15
            // 0b0011 --> d03 --> 10 / 2 = 05
            // 0b0001 --> d01 --> 00 / 1 = 00
            // 0b0000 --> d00 --> 00 / 1 = 00
            
            proportional = estado_sensores - 30;
            derivative = proportional - last_proportional;
            integral += proportional;

            last_proportional = proportional;

            power_difference = proportional / 1 + integral / 15 + derivative * 3 / 2;
             
            if (power_difference > max_power) {
                power_difference = max_power;
            }
            if (power_difference < -max_power) {
                power_difference = -max_power;
            }
             
            if (power_difference < 0) {
                PWM1_VEL(max_power + power_difference);
                PWM2_VEL(max_power);
            } else {
                PWM1_VEL(max_power);
                PWM2_VEL(max_power - power_difference);
            }

        }

        // fin de tareas, para poder empezar de nuevo
        PWM1_VEL(0);
        PWM2_VEL(0);
        _delay_ms(50); //rebote botón

        proportional = 0;
        last_proportional = 0;
        derivative = 0;
        integral = 0;
        power_difference = 0;

        while (BOTON_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}
