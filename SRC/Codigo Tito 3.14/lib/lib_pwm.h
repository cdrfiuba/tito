/*
	Puertos:
			* OC1A, OC1B y 4 genericos
	Timers:
			* Timer 1
	Interrupciones:
			* TIMER1_OVF_vect
*/

#ifndef __PWM_H__
#define __PWM_H__

/*******************************************************
* Constantes
*******************************************************/ 
// COM1A = 11
// COM1B = 11
// WGM = 8 (para usar un TOP fijo)
// el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
#define PRESCALER_PWM_OFF	(0<<CS12)|(0<<CS11)|(0<<CS10)
#define PRESCALER_PWM_ON	(0<<CS12)|(0<<CS11)|(1<<CS10)

#define PWM_TCCR1A (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(1<<WGM10)
#define PWM_TCCR1B (1<<WGM13)|(0<<WGM12)|PRESCALER_PWM_OFF

#define PWM_TCCR0A (1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0)|(0<<WGM01)|(1<<WGM00)
#define PWM_TCCR0B (0<<FOC0A)|(0<<FOC0B)|(1<<WGM12)|PRESCALER_PWM_OFF

#define PWM_FREC 800 // Frecuencia PWM
#define PWM_ICR1  F_CPU/(2*1*PWM_FREC) // Calcula ICR1

// Macros para setear la vel de los motores: 0% - 100%
#define PWM1_VEL(velocidad) (vel_motor_1 = velocidad*PWM_ICR1/100)
#define PWM2_VEL(velocidad) (vel_motor_2 = velocidad*PWM_ICR1/100)

#define PORT_NAME_PWM1 B
#define PIN_NUM_PWM1 1	//M

#define PORT_PWM1 def_port_reg(PORT_NAME_PWM1)
#define PIN_PWM1 def_pin_reg(PORT_NAME_PWM1)
#define DDR_PWM1 def_ddr_reg(PORT_NAME_PWM1)

#define PORT_NAME_PWM2 B
#define PIN_NUM_PWM2 2	//M

#define PORT_PWM2 def_port_reg(PORT_NAME_PWM2)
#define PIN_PWM2 def_pin_reg(PORT_NAME_PWM2)
#define DDR_PWM2 def_ddr_reg(PORT_NAME_PWM2)

// PINES DE SENTIDO DE GIRO
#define PORT_NAME_MOT1_S1 D
#define PORT_NAME_MOT1_S2 D
#define PORT_NAME_MOT2_S1 C	//M
#define PORT_NAME_MOT2_S2 C	//M

#define PORT_NUM_MOT1_S1 1
#define PORT_NUM_MOT1_S2 0	//M
#define PORT_NUM_MOT2_S1 4	//M
#define PORT_NUM_MOT2_S2 5	//M

#define PORT_MOT1_S1 def_port_reg(PORT_NAME_MOT1_S1)
#define PIN_MOT1_S1 def_pin_reg(PORT_NAME_MOT1_S1)
#define DDR_MOT1_S1 def_ddr_reg(PORT_NAME_MOT1_S1)

#define PORT_MOT1_S2 def_port_reg(PORT_NAME_MOT1_S2)
#define PIN_MOT1_S2 def_pin_reg(PORT_NAME_MOT1_S2)
#define DDR_MOT1_S2 def_ddr_reg(PORT_NAME_MOT1_S2)

#define PORT_MOT2_S1 def_port_reg(PORT_NAME_MOT2_S1)
#define PIN_MOT2_S1 def_pin_reg(PORT_NAME_MOT2_S1)
#define DDR_MOT2_S1 def_ddr_reg(PORT_NAME_MOT2_S1)

#define PORT_MOT2_S2 def_port_reg(PORT_NAME_MOT2_S2)
#define PIN_MOT2_S2 def_pin_reg(PORT_NAME_MOT2_S2)
#define DDR_MOT2_S2 def_ddr_reg(PORT_NAME_MOT2_S2)

/*******************************************************
* Tipos
*******************************************************/ 
typedef enum {LIBRE, AD, AT, DET} sentido_t;

/*******************************************************
* Variables globales
*******************************************************/ 
// Variables para las velocidades de los dos motores.
volatile uint16_t vel_motor_1;
volatile uint16_t vel_motor_2;

/*******************************************************
* Prototipos
*******************************************************/ 
// Metodo para configurar los dos PWM del timer 1. Los activa con un ds del 50%
void pwm_config(void);

// Metodo para modificar el valor del DS.
//inline void set_vel_motor_1( uint16_t new_ocr1a );
//inline void set_vel_motor_2( uint16_t new_ocr1b );NO VA MAS. SE HACE CON LA MACRO

// Metodo para prender y apagar los PWM. Pone o saca el prescaler.
void pwm_start(void);
void pwm_stop(void);

// Sentido de giro de los motores
inline void mot1_sent(sentido_t sentido);
inline void mot2_sent(sentido_t sentido);

/*******************************************************
* Macros
*******************************************************/ 

#define concat(a,b)	a ## b
#define def_port_reg(name)	concat(PORT, name) 
#define def_pin_reg(name)	concat(PIN, name) 
#define def_ddr_reg(name)	concat(DDR, name) 

#endif
