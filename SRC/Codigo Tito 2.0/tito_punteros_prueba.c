#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"
#include <avr/pgmspace.h>

void mover_motor_izquierda() {
    PWM1_VEL(0);
    PWM2_VEL(100);
}

void mover_motor_derecha() {
    PWM1_VEL(100);
    PWM2_VEL(0);
}

void (*funciones[2])(void);// = {mover_motor_izquierda, mover_motor_derecha};


/**
 función principal
*/
int main() {

    startup();

    mot1_sent(AD);
    mot2_sent(AD);
    PWM1_VEL(100);
    PWM2_VEL(100);
    
    funciones[0] = mover_motor_izquierda;
    funciones[1] = mover_motor_derecha;
    
    while (1) {
        _delay_ms(2000);
        
        (*funciones[0])();

        _delay_ms(2000);

        (*funciones[1])();
    }
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
