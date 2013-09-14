#include "motores.h"
#include <avr/io.h>
#include "common.h"

void pwm_config(void) {

    // El objetivo es tener dos PWM negados en IN1A y en IN2A.
    // En el mismo período de PWM, si el duty cycle pasa más tiempo en IN1A,
    // el motor se mueve en un sentido. Si pasa más tiempo en IN2A, se
    // mueve en el otro sentido. Si pasa el mismo tiempo tanto en IN1A como
    // en IN2B, el motor no se mueve.
    // Se pone el Waveform generation mode en modo 1: PWM, phase correct; TOP = 0xFF; Update OCRx at TOP; TOV flag set on BOTTOM.
    // Un PWM se configura en Set OCxn when up-counting, Clear OCxn when down-counting, mientras que el otro se configura al revés, Set OCxn when down-counting, Clear OCxn when up-counting. Esto permite que ambos PWM estén siempre negados entre sí.
    // El Clock Select va sin prescaler para que el PWM sea lo más rápido y responsivo posible. Poner el prescaler implica prender el timer.
    TCCR0A = (1 << COM0A1) | (0 << COM0A0) | (1 << COM0B1) | (1 << COM0B0) | (0 << WGM01) | (1 << WGM00);
    TCCR0B = (0 << FOC0A) | (0 << FOC0B) | (1 << WGM02) | (0 << CS02) | (0 << CS01) | (1 << CS00);

    // configura los puertos como salida
	SetBit (DDR_MOTOR_DERECHO_ENABLE, MOTOR_DERECHO_ENABLE_NUMBER);
	SetBit (DDR_MOTOR_IZQUIERDO_ENABLE, MOTOR_IZQUIERDO_ENABLE_NUMBER); 

	SetBit (DDR_MOTOR_IZQUIERDO_1, MOTOR_IZQUIERDO_1_NUMBER);
	SetBit (DDR_MOTOR_IZQUIERDO_2, MOTOR_IZQUIERDO_2_NUMBER);
	SetBit (DDR_MOTOR_DERECHO_1, MOTOR_DERECHO_1_NUMBER);
	SetBit (DDR_MOTOR_DERECHO_2, MOTOR_DERECHO_2_NUMBER);

    // habilita los ENABLE de los motores, que deben ir siempre en 1
    SetBit (PORT_MOTOR_DERECHO_ENABLE, MOTOR_DERECHO_ENABLE_NUMBER);
    SetBit (PORT_MOTOR_IZQUIERDO_ENABLE, MOTOR_IZQUIERDO_ENABLE_NUMBER);


}
