#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL
#include "lib_pwm.h"

void pwm_config(void){
	// Configuramos los puertos como salidas en cero
	DDR_PWM1 |= _BV(PIN_NUM_PWM1);
	DDR_PWM2 |= _BV(PIN_NUM_PWM2);

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

//	OCR1A = 0;
//	OCR1B = 0;

	// Activamos la IRQ de OVF
	TIMSK |= (_BV(OCIE1B) | _BV(OCIE1A)) ;

	// Prende los motores
    SetBit(PORT_PWM1,PIN_NUM_PWM1);
    SetBit(PORT_PWM2,PIN_NUM_PWM2);
    ClearBit(PORT_MOT1_S2,PORT_NUM_MOT1_S2);
    ClearBit(PORT_MOT2_S2,PORT_NUM_MOT2_S2);
    
    SetBit(PORT_MOT1_S1,PORT_NUM_MOT1_S1);
    SetBit(PORT_MOT2_S1,PORT_NUM_MOT2_S1);
    
}

/*inline void set_vel_motor_1( uint8_t velocidad ){
	vel_motor_1 = velocidad*PWM_ICR1/255;
}   DEFINIDO EN EL .H!!!*/

/*inline void set_vel_motor_2( uint16_t velocidad ){
	vel_motor_2 = velocidad ;
}   DEFINIDO EN EL .H!!!*/

// Sentido de giro del motor 1
// LIBRE, AD, AT, DET
inline void mot1_vel(uint16_t velocidad){
    OCR1A=velocidad;
}

inline void mot2_vel(uint16_t velocidad){
    OCR1B=velocidad;
}
// Sentido de giro del motor 2
// LIBRE, AD, AT, DET


void pwm_start(void) {
	TCCR1B |= PRESCALER_PWM_ON;
}

void pwm_stop(void) {
	TCCR1B &=~ PRESCALER_PWM_OFF;
}

ISR( TIMER1_COMPA_vect ) { 
    if(IsBitSet(PORT_MOT1_S1,PORT_NUM_MOT1_S1)){
        ClearBit(PORT_MOT1_S1,PORT_NUM_MOT1_S1);
        SetBit(PORT_MOT1_S2,PORT_NUM_MOT1_S2);
    }
    else{
        SetBit(PORT_MOT1_S1,PORT_NUM_MOT1_S1);
        ClearBit(PORT_MOT1_S2,PORT_NUM_MOT1_S2);
    }
}

ISR( TIMER1_COMPB_vect ) { 
    if(IsBitSet(PORT_MOT2_S1,PORT_NUM_MOT2_S1)){
        ClearBit(PORT_MOT2_S1,PORT_NUM_MOT2_S1);
        SetBit(PORT_MOT2_S2,PORT_NUM_MOT2_S2);
    }
    else{
        SetBit(PORT_MOT2_S1,PORT_NUM_MOT2_S1);
        ClearBit(PORT_MOT2_S2,PORT_NUM_MOT2_S2);
    }
}
