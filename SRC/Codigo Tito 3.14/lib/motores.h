#ifndef _MOTORES_
#define _MOTORES_

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

#define PORT_MOTOR_SERVO_NAME      B
#define MOTOR_SERVO_NUMBER         3
#define PORT_MOTOR_SERVO		def_port_reg(PORT_MOTOR_SERVO_NAME)
#define PIN_MOTOR_SERVO			def_pin_reg(PORT_MOTOR_SERVO_NAME)
#define DDR_MOTOR_SERVO			def_ddr_reg(PORT_MOTOR_SERVO_NAME)

// el ángulo va de 0 a 180
#define servo_angulo(ang)    OCR2A = (ang / 180 * 256)

void pwm_config(void);
void pwm_on(void);
void pwm_off(void);
void motores_on(void);
void motores_off(void);
void servo_on(void);
void servo_off(void);
void timer2_init(void);


#endif
