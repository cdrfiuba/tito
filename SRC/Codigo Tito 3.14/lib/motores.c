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
    TCCR0B = (0 << FOC0A) | (0 << FOC0B) | (0 << WGM02) | (0 << CS02) | (0 << CS01) | (0 << CS00);
    //TIMSK0 = (1<< OCIE0B) |(1<< OCIE0B) | (1<<TOIE0);

    TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (0 << WGM11) | (1 << WGM10);
    TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (0 << WGM12) | (0 << CS12) | (0 << CS11) | (0 << CS10);
    TCCR1C = (0 << FOC1A) | (0 << FOC1B); 
 
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


inline void pwm_on(void) {
    TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
    TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
}

inline void pwm_off(void) {
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

inline void motores_on(void) {
    pwm_on();
    SetBit (PORT_MOTOR_DERECHO_ENABLE, MOTOR_DERECHO_ENABLE_NUMBER);
    SetBit (PORT_MOTOR_IZQUIERDO_ENABLE, MOTOR_IZQUIERDO_ENABLE_NUMBER);
}

inline void motores_off(void) {
    pwm_off();
    ClearBit (PORT_MOTOR_DERECHO_ENABLE, MOTOR_DERECHO_ENABLE_NUMBER);
    ClearBit (PORT_MOTOR_IZQUIERDO_ENABLE, MOTOR_IZQUIERDO_ENABLE_NUMBER);
}
