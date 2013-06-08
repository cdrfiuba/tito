#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib_pwm.h"
#include "common.h"

void pwm_config(void){
	// Configuramos los puertos como salidas en cero
	// enables de los motores
	SetBit (DDR_MOTOR_DERECHO_ENABLE, MOTOR_DERECHO_ENABLE_NUMBER);
	SetBit (DDR_MOTOR_IZQUIERDO_ENABLE, MOTOR_IZQUIERDO_ENABLE_NUMBER);
	SetBit (DDR_MOTOR_DERECHO_1, MOTOR_DERECHO_1_NUMBER);
	SetBit (DDR_MOTOR_DERECHO_2, MOTOR_DERECHO_2_NUMBER);
	SetBit (DDR_MOTOR_IZQUIERDO_1, MOTOR_IZQUIERDO_1_NUMBER);
	SetBit (DDR_MOTOR_IZQUIERDO_2, MOTOR_IZQUIERDO_2_NUMBER);

	// PORT_PWM1 &=~ _BV(PIN_NUM_PWM1);
	// PORT_PWM2 &=~ _BV(PIN_NUM_PWM2);

	// pines de sentido de giro
	ClearBit (PORT_MOTOR_DERECHO_ENABLE, MOTOR_DERECHO_ENABLE_NUMBER);
	ClearBit (PORT_MOTOR_IZQUIERDO_ENABLE, MOTOR_IZQUIERDO_ENABLE_NUMBER);
	ClearBit (PORT_MOTOR_DERECHO_1, MOTOR_DERECHO_1_NUMBER);
	ClearBit (PORT_MOTOR_DERECHO_2, MOTOR_DERECHO_2_NUMBER);
	ClearBit (PORT_MOTOR_IZQUIERDO_1, MOTOR_IZQUIERDO_1_NUMBER);
	ClearBit (PORT_MOTOR_IZQUIERDO_2, MOTOR_IZQUIERDO_2_NUMBER);
	
	// Configuramos el PWM
	TCCR1A = PWM_TCCR1A;
	TCCR1B = PWM_TCCR1B;

	TCCR0A = PWM_TCCR0A;
	TCCR0B = PWM_TCCR0B;


	OCR1A = 128;
	//OCR1B = 0;
	OCR0A = 128;
	//OCR0B = 0;

	// Activamos la IRQ de OVF
	//TIMSK1 |= _BV(TOIE1) ;

	// Apaga los motores
	//mot1_sent(LIBRE);
	//mot2_sent(LIBRE);
}

/*inline void set_vel_motor_1( uint8_t velocidad ){
	vel_motor_1 = velocidad*PWM_ICR1/255;
}   DEFINIDO EN EL .H!!!*/

/*inline void set_vel_motor_2( uint16_t velocidad ){
	vel_motor_2 = velocidad ;
}   DEFINIDO EN EL .H!!!*/

void pwm_start(void) {
	TCCR1B |= PRESCALER_PWM_ON;
	TCCR0B |= PRESCALER_PWM_ON;
}

void pwm_stop(void) {
	TCCR1B &= PRESCALER_PWM_OFF;
	TCCR0B &= PRESCALER_PWM_OFF;
}

/*
ISR( TIMER0_OVF_vect ) { 
	OCR0A = vel_motor_1_1 ;
	OCR0B = vel_motor_1_2 ;
}

ISR( TIMER1_OVF_vect ) { 
	OCR1A = vel_motor_2_1 ;
	OCR1B = vel_motor_2_2 ;
}
*/
