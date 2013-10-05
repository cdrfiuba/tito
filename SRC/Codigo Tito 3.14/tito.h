#ifndef HEADER_TITO
#define HEADER_TITO

#include "lib/motores.h"
#include "lib/common.h"
#include "velocidades.h"

/**
 Prototipos
*/
void startup (void);

inline void setear_conversor(uint8_t sensor){
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)); 
    ADMUX |= sensor; 
}

#define CONVIRTIENDO (ADCSRA & (1 << ADSC))
#define LEER_CONVERSION ADCH

void configurar_sensores(void){

    ADMUX = ( (0 << REFS1) | (1 << REFS0) | (1 << ADLAR) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0) );
    ADCSRA = ( (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE)  | (0 << ADPS2) | (0 << ADPS1)| (0 << ADPS0) );
    ADCSRB = (  (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0) | (0 << ACME) );

}

#define MAX_SENSORES 4
#define apagar_adc() (ADCSRA &= ~(1 << ADSC))
#define prender_adc() (ADCSRA |= (1 << ADSC))


inline void obtener_sensores(uint8_t *sensores){
    uint8_t i;
    apagar_adc();    

    for (i = 0; i < MAX_SENSORES ; i++){
        setear_conversor (i);
        prender_adc();
        //while(CONVIRTIENDO);
        sensores[i] = LEER_CONVERSION;
        apagar_adc();        
    } 
}


/**
 estados y eventos para la fsm
*/
typedef enum estados {
    
    ST_EN_LINEA,

    ST_YENDOSE_POCO_POR_DERECHA,
    ST_YENDOSE_BASTANTE_POR_DERECHA,
    ST_YENDOSE_MUCHO_POR_DERECHA,
    ST_AFUERA_POR_DERECHA,
    ST_VOLVIENDO_POR_DERECHA,/*
    ST_VOLVIO_POR_DERECHA,*/

    ST_YENDOSE_POCO_POR_IZQUIERDA,
    ST_YENDOSE_BASTANTE_POR_IZQUIERDA,
    ST_YENDOSE_MUCHO_POR_IZQUIERDA,
    ST_AFUERA_POR_IZQUIERDA,
    ST_VOLVIENDO_POR_IZQUIERDA/*,
    ST_VOLVIO_POR_IZQUIERDA*/
    
    //ST_MAX_ESTADOS

} estados_t;

// (los sensores se componen como:
//  S_IZQ_AFUERA | S_IZQ_CENTRO | S_DER_CENTRO | S_DER_AFUERA )
typedef enum eventos {
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
    EV_CUALQUIERA = 16
} eventos_t;

typedef enum tipos_estado {
    TIPO_RECTA = 0,
    TIPO_CURVA = 1
} tipos_estado_t;

// m�quina de estados
typedef struct {
    estados_t estado;
    eventos_t sensores;
    estados_t estado_nuevo;
    //tipos_estado_t tipo_estado; //RECTA o CURVA
} tTransition;

// configuraci�n de los puertos

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

#define CANCELAR_INERCIA(us_ad, us_at) motor1_velocidad(100);_delay_us(us_ad);motor1_velocidad(-100);_delay_us(us_at);

#endif
