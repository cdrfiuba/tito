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

#define PORT_MOTOR_DERECHO_1_NAME      B
#define MOTOR_DERECHO_1_NUMBER         1
#define PORT_MOTOR_DERECHO_1		def_port_reg(PORT_MOTOR_DERECHO_1_NAME)
#define PIN_MOTOR_DERECHO_1			def_pin_reg(PORT_MOTOR_DERECHO_1_NAME)
#define DDR_MOTOR_DERECHO_1			def_ddr_reg(PORT_MOTOR_DERECHO_1_NAME)

#define PORT_MOTOR_DERECHO_2_NAME      B
#define MOTOR_DERECHO_2_NUMBER         2
#define PORT_MOTOR_DERECHO_2		def_port_reg(PORT_MOTOR_DERECHO_2_NAME)
#define PIN_MOTOR_DERECHO_2			def_pin_reg(PORT_MOTOR_DERECHO_2_NAME)
#define DDR_MOTOR_DERECHO_2			def_ddr_reg(PORT_MOTOR_DERECHO_2_NAME)

#define PORT_MOTOR_DERECHO_ENABLE_NAME      B
#define MOTOR_DERECHO_ENABLE_NUMBER         7
#define PORT_MOTOR_DERECHO_ENABLE		def_port_reg(PORT_MOTOR_DERECHO_ENABLE_NAME)
#define PIN_MOTOR_DERECHO_ENABLE		def_pin_reg(PORT_MOTOR_DERECHO_ENABLE_NAME)
#define DDR_MOTOR_DERECHO_ENABLE		def_ddr_reg(PORT_MOTOR_DERECHO_ENABLE_NAME)

#define PORT_MOTOR_IZQUIERDO_1_NAME      D
#define MOTOR_IZQUIERDO_1_NUMBER         6
#define PORT_MOTOR_IZQUIERDO_1		def_port_reg(PORT_MOTOR_IZQUIERDO_1_NAME)
#define PIN_MOTOR_IZQUIERDO_1		def_pin_reg(PORT_MOTOR_IZQUIERDO_1_NAME)
#define DDR_MOTOR_IZQUIERDO_1		def_ddr_reg(PORT_MOTOR_IZQUIERDO_1_NAME)

#define PORT_MOTOR_IZQUIERDO_2_NAME      D
#define MOTOR_IZQUIERDO_2_NUMBER         5
#define PORT_MOTOR_IZQUIERDO_2		def_port_reg(PORT_MOTOR_IZQUIERDO_2_NAME)
#define PIN_MOTOR_IZQUIERDO_2		def_pin_reg(PORT_MOTOR_IZQUIERDO_2_NAME)
#define DDR_MOTOR_IZQUIERDO_2		def_ddr_reg(PORT_MOTOR_IZQUIERDO_2_NAME)

#define PORT_MOTOR_IZQUIERDO_ENABLE_NAME      B
#define MOTOR_IZQUIERDO_ENABLE_NUMBER         6
#define PORT_MOTOR_IZQUIERDO_ENABLE		def_port_reg(PORT_MOTOR_IZQUIERDO_ENABLE_NAME)
#define PIN_MOTOR_IZQUIERDO_ENABLE		def_pin_reg(PORT_MOTOR_IZQUIERDO_ENABLE_NAME)
#define DDR_MOTOR_IZQUIERDO_ENABLE		def_ddr_reg(PORT_MOTOR_IZQUIERDO_ENABLE_NAME)




/*******************************************************
* Constantes
*******************************************************/ 
// COM1A = 11
// COM1B = 11
// WGM = 8 (para usar un TOP fijo)
// el "prescaler" en 1 (CS12 = 0 , CS11 =0 , CS10 = 1)
#define PRESCALER_PWM_OFF	~((1<<CS12)|(1<<CS11)|(1<<CS10))
#define PRESCALER_PWM_ON	(0<<CS12)|(0<<CS11)|(1<<CS10)

#define PWM_TCCR1A (1<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(1<<COM1B0)|(0<<WGM11)|(1<<WGM10)
#define PWM_TCCR1B (0<<WGM13)|(0<<WGM12)|PRESCALER_PWM_OFF

#define PWM_TCCR0A (1<<COM0A1)|(0<<COM0A0)|(0<<COM0B1)|(1<<COM0B0)|(0<<WGM01)|(1<<WGM00)
#define PWM_TCCR0B (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|PRESCALER_PWM_OFF

//#define PWM_FREC 800 // Frecuencia PWM
//#define PWM_ICR1  F_CPU/(2*1*PWM_FREC) // Calcula ICR1

// Macros para setear la vel de los motores: 0% - 100%
//#define PWM1_VEL(velocidad) (vel_motor_1 = velocidad*PWM_ICR1/100)
//#define PWM2_VEL(velocidad) (vel_motor_2 = velocidad*PWM_ICR1/100)

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

#endif
