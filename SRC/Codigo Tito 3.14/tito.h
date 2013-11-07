#ifndef HEADER_TITO
#define HEADER_TITO

#include "lib/motores.h"
#include "lib/common.h"
#include "velocidades.h"

/**
 Prototipos
*/
void startup (void);

#define CONVIRTIENDO_AD IsBitSet(ADCSRA, ADSC)
#define LEER_CONVERSION_AD ADCH
#define MAX_SENSORES 6
#define MAX_SENSORES_INIT {0, 0, 0, 0, 0, 0}
#define detener_conversion_ad() (ADCSRA &= ~(1 << ADSC))
#define iniciar_conversion_ad() (ADCSRA |= (1 << ADSC))

//#define CENTRO_DE_LINEA 1500 /* 4 sensores */
#define CENTRO_DE_LINEA 2500 /* 6 sensores */
#define VALOR_MAX_INT32 2147483647L
#define VALOR_MAX_INT16 32767
#define VALOR_MAX_ERR_P CENTRO_DE_LINEA

#define DELAY_ARRANQUE 10

// números de sensores
#define S1 5
#define S2 0
#define S3 1
#define S4 2
#define S5 3
#define S6 4

//estados
typedef enum estados {
    ST_EN_PISTA,
    ST_AFUERA
} estados_t;
typedef enum bordes {
	BORDE_IZQUIERDA,
	BORDE_DERECHA
} bordes_t;

// configuración de los puertos
#define PORT_LED_1_NAME      D
#define LED_1_NUMBER         4
#define PORT_LED_1		def_port_reg(PORT_LED_1_NAME)
#define PIN_LED_1		def_pin_reg(PORT_LED_1_NAME)
#define DDR_LED_1		def_ddr_reg(PORT_LED_1_NAME)

#define PORT_LED_2_NAME      D 
#define LED_2_NUMBER         7
#define PORT_LED_2		def_port_reg(PORT_LED_2_NAME)
#define PIN_LED_2		def_pin_reg(PORT_LED_2_NAME)
#define DDR_LED_2		def_ddr_reg(PORT_LED_2_NAME)

#define PORT_LED_3_NAME      B     //conectado al programador
#define LED_3_NUMBER         4
#define PORT_LED_3		def_port_reg(PORT_LED_3_NAME)
#define PIN_LED_3		def_pin_reg(PORT_LED_3_NAME)
#define DDR_LED_3		def_ddr_reg(PORT_LED_3_NAME)

#define PORT_LED_4_NAME      B
#define LED_4_NUMBER         0
#define PORT_LED_4		def_port_reg(PORT_LED_4_NAME)
#define PIN_LED_4		def_pin_reg(PORT_LED_4_NAME)
#define DDR_LED_4		def_ddr_reg(PORT_LED_4_NAME)

#define PORT_SENSOR_1_NAME      C
#define SENSOR_1_NUMBER         3
#define PORT_SENSOR_1		def_port_reg(PORT_SENSOR_1_NAME)
#define PIN_SENSOR_1		def_pin_reg(PORT_SENSOR_1_NAME)
#define DDR_SENSOR_1		def_ddr_reg(PORT_SENSOR_1_NAME)

#define PORT_SENSOR_2_NAME      C
#define SENSOR_2_NUMBER         2
#define PORT_SENSOR_2		def_port_reg(PORT_SENSOR_2_NAME)
#define PIN_SENSOR_2		def_pin_reg(PORT_SENSOR_2_NAME)
#define DDR_SENSOR_2		def_ddr_reg(PORT_SENSOR_2_NAME)

#define PORT_SENSOR_3_NAME      C
#define SENSOR_3_NUMBER         1
#define PORT_SENSOR_3		def_port_reg(PORT_SENSOR_3_NAME)
#define PIN_SENSOR_3		def_pin_reg(PORT_SENSOR_3_NAME)
#define DDR_SENSOR_3		def_ddr_reg(PORT_SENSOR_3_NAME)

#define PORT_SENSOR_4_NAME      C
#define SENSOR_4_NUMBER			0
#define PORT_SENSOR_4		def_port_reg(PORT_SENSOR_4_NAME)
#define PIN_SENSOR_4		def_pin_reg(PORT_SENSOR_4_NAME)
#define DDR_SENSOR_4		def_ddr_reg(PORT_SENSOR_4_NAME)

#define PORT_SENSOR_5_NAME      C
#define SENSOR_5_NUMBER         4
#define PORT_SENSOR_5		def_port_reg(PORT_SENSOR_5_NAME)
#define PIN_SENSOR_5		def_pin_reg(PORT_SENSOR_5_NAME)
#define DDR_SENSOR_5		def_ddr_reg(PORT_SENSOR_5_NAME)

#define PORT_SENSOR_6_NAME      C
#define SENSOR_6_NUMBER         5
#define PORT_SENSOR_6		def_port_reg(PORT_SENSOR_6_NAME)
#define PIN_SENSOR_6		def_pin_reg(PORT_SENSOR_6_NAME)
#define DDR_SENSOR_6		def_ddr_reg(PORT_SENSOR_6_NAME)

#define PORT_BOTON1_NAME      B
#define BOTON1_NUMBER         5
#define PORT_BOTON1		def_port_reg(PORT_BOTON1_NAME)
#define PIN_BOTON1		def_pin_reg(PORT_BOTON1_NAME)
#define DDR_BOTON1		def_ddr_reg(PORT_BOTON1_NAME)

#define PORT_BOTON2_NAME      PORT_INTERRUPCION_2_NAME
#define BOTON2_NUMBER         INTERRUPCION_2_NUMBER
#define PORT_BOTON2		def_port_reg(PORT_BOTON2_NAME)
#define PIN_BOTON2		def_pin_reg(PORT_BOTON2_NAME)
#define DDR_BOTON2		def_ddr_reg(PORT_BOTON2_NAME)

#define PORT_INTERRUPCION_1_NAME      D
#define INTERRUPCION_1_NUMBER         2
#define PORT_INTERRUPCION_1		def_port_reg(PORT_INTERRUPCION_1_NAME)
#define PIN_INTERRUPCION_1		def_pin_reg(PORT_INTERRUPCION_1_NAME)
#define DDR_INTERRUPCION_1		def_ddr_reg(PORT_INTERRUPCION_1_NAME)

#define PORT_INTERRUPCION_2_NAME      D
#define INTERRUPCION_2_NUMBER         3
#define PORT_INTERRUPCION_2		def_port_reg(PORT_INTERRUPCION_2_NAME)
#define PIN_INTERRUPCION_2		def_pin_reg(PORT_INTERRUPCION_2_NAME)
#define DDR_INTERRUPCION_2		def_ddr_reg(PORT_INTERRUPCION_2_NAME)

#define SENSOR_IZQUIERDA_AFUERA		IsBitSet(PIN_SENSOR_1, SENSOR_1_NUMBER)
#define SENSOR_IZQUIERDA_CENTRO		IsBitSet(PIN_SENSOR_2, SENSOR_2_NUMBER)
#define SENSOR_DERECHA_CENTRO		IsBitSet(PIN_SENSOR_3, SENSOR_3_NUMBER)
#define SENSOR_DERECHA_AFUERA		IsBitSet(PIN_SENSOR_4, SENSOR_4_NUMBER)

#define BOTON1_APRETADO         (!(PIN_BOTON1&(1<<BOTON1_NUMBER)))
#define BOTON1_NO_APRETADO     (PIN_BOTON1&(1<<BOTON1_NUMBER))

#define BOTON2_APRETADO         (!(PIN_BOTON2&(1<<BOTON2_NUMBER)))
#define BOTON2_NO_APRETADO     (PIN_BOTON2&(1<<BOTON2_NUMBER))

// la velocidad va de -100 a 100
#define motor1_velocidad(vel)         OCR0A = (vel * 1.27 * COEFICIENTE_IZQUIERDA + 127); OCR0B = (vel * 1.27 * COEFICIENTE_IZQUIERDA + 127)
#define motor2_velocidad(vel)         OCR1AL = (vel * 1.27 * COEFICIENTE_DERECHA + 127); OCR1BL = (vel * 1.27 * COEFICIENTE_DERECHA + 127)

#define motor1_velocidad_pid(vel)     OCR0A = vel; OCR0B = vel
#define motor2_velocidad_pid(vel)     OCR1AL = vel; OCR1BL = vel

#define CANCELAR_INERCIA(us_ad, us_at) motor1_velocidad(100);_delay_us(us_ad);motor1_velocidad(-100);_delay_us(us_at);

#endif
