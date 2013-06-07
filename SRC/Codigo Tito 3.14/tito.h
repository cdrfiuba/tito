#ifndef HEADER_TITO
#define HEADER_TITO

#include "velocidades.h"
/**
 Prototipos
*/
void startup (void);
//void prueba_frenado(void);

/**
 estados y eventos para la fsm
*/
typedef enum estados {
    
    ST_EN_LINEA = 0,

    ST_YENDOSE_POCO_POR_DERECHA = 1,
    ST_YENDOSE_MUCHO_POR_DERECHA = 2,
    ST_AFUERA_POR_DERECHA = 3,
    ST_VOLVIENDO_POR_DERECHA = 4,
    ST_VOLVIO_POR_DERECHA = 5,

    ST_YENDOSE_POCO_POR_IZQUIERDA = 6,
    ST_YENDOSE_MUCHO_POR_IZQUIERDA = 7,
    ST_AFUERA_POR_IZQUIERDA = 8,
    ST_VOLVIENDO_POR_IZQUIERDA = 9,
    ST_VOLVIO_POR_IZQUIERDA = 10,
    
    ST_MAX_ESTADOS = 11

} estados_t;
typedef enum estados_resumidos {
    EL=0,

    YPPD=1,
    YMPD=2,
    APD=3,
    VEPD=4,
    VOPD=5,

    YPPI=6,
    YMPI=7,
    API=8,
    VEPI=9,
    VOPI=10,

    ME=11
} estados_resumidos_t;
// (los sensores se componen como:
//  S_IZQ_AFUERA | S_IZQ_CENTRO | S_DER_CENTRO | S_DER_AFUERA )
typedef enum eventos {
    EV_CUALQUIERA = 16,

    EV_SENSORES_NNNN = 0,
    EV_SENSORES_NNNB = 1,
    EV_SENSORES_NNBN = 2,
    EV_SENSORES_NNBB = 3,
    EV_SENSORES_NBNN = 4,
    EV_SENSORES_NBNB = 5,
    EV_SENSORES_NBBN = 6,
    EV_SENSORES_NBBB = 7,
    EV_SENSORES_BNNN = 8,
    EV_SENSORES_BNNB = 9,
    EV_SENSORES_BNBN = 10,
    EV_SENSORES_BNBB = 11,
    EV_SENSORES_BBNN = 12,
    EV_SENSORES_BBNB = 13,
    EV_SENSORES_BBBN = 14,
    EV_SENSORES_BBBB = 15,
    EV_MAX_SENSORES = 16
} eventos_t;
// PARA 
typedef enum tipos_estado {
    TIPO_RECTA = 0,
    TIPO_CURVA = 1
} tipos_estado_t;

#define PORT_LED_1_NAME      B
#define LED_1_NUMBER         0
#define PORT_LED_1		def_port_reg(PORT_LED_1_NAME)
#define PIN_LED_1		def_pin_reg(PORT_LED_1_NAME)
#define DDR_LED_1		def_ddr_reg(PORT_LED_1_NAME)

#define PORT_LED_2_NAME      D
#define LED_2_NUMBER         4
#define PORT_LED_2		def_port_reg(PORT_LED_2_NAME)
#define PIN_LED_2		def_pin_reg(PORT_LED_2_NAME)
#define DDR_LED_2		def_ddr_reg(PORT_LED_2_NAME)

#define PORT_LED_3_NAME      D
#define LED_3_NUMBER         7
#define PORT_LED_3		def_port_reg(PORT_LED_3_NAME)
#define PIN_LED_3		def_pin_reg(PORT_LED_3_NAME)
#define DDR_LED_3		def_ddr_reg(PORT_LED_3_NAME)

#define PORT_LED_4_NAME      B
#define LED_4_NUMBER         4
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

#define PORT_BOTON_NAME      B
#define BOTON_NUMBER         4
#define PORT_BOTON		def_port_reg(PORT_BOTON_NAME)
#define PIN_BOTON		def_pin_reg(PORT_BOTON_NAME)
#define DDR_BOTON		def_ddr_reg(PORT_BOTON_NAME)

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



#define SetBit(Byte,Bit)		(Byte |= (1<<Bit))
#define ClearBit(Byte,Bit)		(Byte &= (~(1<<Bit)))
#define IsBitSet(Byte,Bit)		((Byte&(1<<Bit)) ? 1 : 0)
//#define IsBitSet(Byte,Bit)	((Byte>>Bit) & 1)

#define SENSOR_IZQUIERDA_AFUERA		IsBitSet(PIN_SENSOR_1, SENSOR_1_NUMBER)
#define SENSOR_IZQUIERDA_CENTRO		IsBitSet(PIN_SENSOR_2, SENSOR_2_NUMBER)
#define SENSOR_DERECHA_CENTRO		IsBitSet(PIN_SENSOR_3, SENSOR_3_NUMBER)
#define SENSOR_DERECHA_AFUERA		IsBitSet(PIN_SENSOR_4, SENSOR_4_NUMBER)

#define BOTON_APRETADO         (!(PIN_BOTON&(1<<BOTON_NUMBER)))
#define BOTON_NO_APRETADO     (PIN_BOTON&(1<<BOTON_NUMBER))

/*
#define concat(a,b)        a ## b
#define def_port_reg(name)    concat(PORT,name)
#define def_pin_reg(name)    concat(PIN,name)
#define def_ddr_reg(name)    concat(DDR,name)
*/
#endif
