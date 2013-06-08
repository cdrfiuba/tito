#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL
#include "lib_pwm.h"

void pwm_config(void){
	// Configuramos los puertos como salidas en cero
	// enables de los motores
	SetBit (DDR_MOTOR_DERECHO_ENABLE,MOTOR_DERECHO_ENABLE_NUMBER);
	SetBit (DDR_MOTOR_IZQUIERDO_ENABLE,MOTOR_IZQUIERDO_ENABLE_NUMBER);	
	
	PORT_PWM1 &=~ _BV(PIN_NUM_PWM1);
	PORT_PWM2 &=~ _BV(PIN_NUM_PWM2);

	// pines de sentido de giro
	PORT_MOT1_S1 &=~ _BV(PORT_NUM_MOT1_S1); 	
	PORT_MOT1_S2 &=~ _BV(PORT_NUM_MOT1_S2); 	
	PORT_MOT2_S1 &=~ _BV(PORT_NUM_MOT2_S1); 	
	PORT_MOT2_S2 &=~ _BV(PORT_NUM_MOT2_S2); 	
	 	
	DDR_MOT1_S1 |= _BV(PORT_NUM_MOT1_S1); 	
	DDR_MOT1_S2 |= _BV(PORT_NUM_MOT1_S2); 	
	DDR_MOT2_S1 |= _BV(PORT_NUM_MOT2_S1); 	
	DDR_MOT2_S2 |= _BV(PORT_NUM_MOT2_S2);
	
	// Configuramos el PWM
	TCCR1A = PWM_TCCR1A;

	TCCR1B = PWM_TCCR1B; 	
	ICR1 = PWM_ICR1; 

	OCR1A = 0;
	OCR1B = 0;

	// Activamos la IRQ de OVF
	TIMSK1 |= _BV(TOIE1) ;

	// Apaga los motores
	mot1_sent(LIBRE);
	mot2_sent(LIBRE);
}

/*inline void set_vel_motor_1( uint8_t velocidad ){
	vel_motor_1 = velocidad*PWM_ICR1/255;
}   DEFINIDO EN EL .H!!!*/

/*inline void set_vel_motor_2( uint16_t velocidad ){
	vel_motor_2 = velocidad ;
}   DEFINIDO EN EL .H!!!*/

// Sentido de giro del motor 1
// LIBRE, AD, AT, DET
inline void mot1_sent(sentido_t sentido){
	switch(sentido){
		case LIBRE:
			PORT_MOT1_S1 &=~ _BV(PORT_NUM_MOT1_S1);
			PORT_MOT1_S2 &=~ _BV(PORT_NUM_MOT1_S2);
			break;
		case AT:
			PORT_MOT1_S1 |= _BV(PORT_NUM_MOT1_S1);
			PORT_MOT1_S2 &=~ _BV(PORT_NUM_MOT1_S2);
			break;
		case AD:
			PORT_MOT1_S1 &=~ _BV(PORT_NUM_MOT1_S1);
			PORT_MOT1_S2 |= _BV(PORT_NUM_MOT1_S2);
			break;
		case DET:
			PORT_MOT1_S1 |= _BV(PORT_NUM_MOT1_S1);
			PORT_MOT1_S2 |= _BV(PORT_NUM_MOT1_S2);
			break;
	}
}

// Sentido de giro del motor 2
// LIBRE, AD, AT, DET
inline void mot2_sent(sentido_t sentido){
	switch(sentido){
		case LIBRE:
			PORT_MOT2_S1 &=~ _BV(PORT_NUM_MOT2_S1);
			PORT_MOT2_S2 &=~ _BV(PORT_NUM_MOT2_S2);
			break;
		case AT:
			PORT_MOT2_S1 |= _BV(PORT_NUM_MOT2_S1);
			PORT_MOT2_S2 &=~ _BV(PORT_NUM_MOT2_S2);
			break;
		case AD:
			PORT_MOT2_S1 &=~ _BV(PORT_NUM_MOT2_S1);
			PORT_MOT2_S2 |= _BV(PORT_NUM_MOT2_S2);
			break;
		case DET:
			PORT_MOT2_S1 |= _BV(PORT_NUM_MOT2_S1);
			PORT_MOT2_S2 |= _BV(PORT_NUM_MOT2_S2);
			break;
	}
}

void pwm_start(void) {
	TCCR1B |= PRESCALER_PWM_ON;
	TCCR0B |= PRESCALER_PWM_ON;
}

void pwm_stop(void) {
	TCCR1B &=~ PRESCALER_PWM_OFF;
	TCCR0B &=~ PRESCALER_PWM_OFF;
}

ISR( TIMER0_OVF_vect ) { 
	OCR0A = vel_motor_1_1 ;
	OCR0B = vel_motor_1_2 ;
}

ISR( TIMER1_OVF_vect ) { 
	OCR1A = vel_motor_2_1 ;
	OCR1B = vel_motor_2_2 ;
}

