//#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tito.h"
#include "lib/motores.h"
#include "lib/common.h"
//#include "lib/usart.c"

inline void setear_conversor(uint8_t sensor){
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)); 
    ADMUX |= sensor; 
}
void configurar_sensores(void) {
    ADMUX = ( (0 << REFS1) | (1 << REFS0) | (1 << ADLAR) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
    ADCSRA = ( (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIE)  | (0 << ADPS2) | (0 << ADPS1)| (0 << ADPS0) );
    ADCSRB = ( (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0) | (0 << ACME) );
}

void startup () {
// setear puertos de lectura o escritura,
// según corresponda

    // leds
    SetBit (DDR_LED_1, LED_1_NUMBER);
    SetBit (DDR_LED_2, LED_2_NUMBER);
    SetBit (DDR_LED_3, LED_3_NUMBER);
    SetBit (DDR_LED_4, LED_4_NUMBER);

    // sensores
    ClearBit (DDR_SENSOR_1, SENSOR_1_NUMBER);
    ClearBit (DDR_SENSOR_2, SENSOR_2_NUMBER);
    ClearBit (DDR_SENSOR_3, SENSOR_3_NUMBER);
    ClearBit (DDR_SENSOR_4, SENSOR_4_NUMBER);
    ClearBit (DDR_SENSOR_5, SENSOR_5_NUMBER);
    ClearBit (DDR_SENSOR_6, SENSOR_6_NUMBER);

    // botón1
    ClearBit (DDR_BOTON1, BOTON1_NUMBER);
    SetBit (PORT_BOTON1, BOTON1_NUMBER);

    // botón2
    ClearBit (DDR_BOTON2, BOTON2_NUMBER);
    SetBit (PORT_BOTON2, BOTON2_NUMBER);

    // configuración de PWMs en motores.h
    pwm_config();
    
    // configura los sensores para usar ADC
    //configurar_sensores();
    
    // inicialización de puerto serie
    //USART0Setup(USART_BAUDRATE, USART0_CHARSIZE_8BIT, USART0_STOP_1BIT, USART0_PARITY_DIS, USART0_MODE_ASYNC);

    // uno de los motores usa un timer de 16 bits,
    // pero se usa como si fuera de 8, por lo que la
    // parte alta del registro de 16 bits va en 0
    OCR1AH = 0;
    OCR1BH = 0;

    // pone el flag global para activar interrupciones
    //sei();

}

inline void obtener_sensores(uint8_t *sensores) {
    uint8_t i;
    
    for (i = 0; i < MAX_SENSORES ; i++) {
        setear_conversor (i);
        prender_adc();
        while(CONVIRTIENDO);
        sensores[i] = LEER_CONVERSION;
    }
}


void mostrar_sensor_en_leds (uint8_t sensor) {
    uint8_t sensores[MAX_SENSORES] = {0, 0, 0, 0};
    obtener_sensores(sensores);

    if (IsBitSet(sensores[sensor], 8)) {
        SetBit(PORT_LED_1, LED_1_NUMBER);
    } else {
        ClearBit(PORT_LED_1, LED_1_NUMBER);
    }
    if (IsBitSet(sensores[sensor], 7)) {
        SetBit(PORT_LED_2, LED_2_NUMBER);
    } else {
        ClearBit(PORT_LED_2, LED_2_NUMBER);
    }
    if (IsBitSet(sensores[sensor], 6)) {
        SetBit(PORT_LED_3, LED_3_NUMBER);
    } else {
        ClearBit(PORT_LED_3, LED_3_NUMBER);
    }
    if (IsBitSet(sensores[sensor], 5)) {
        SetBit(PORT_LED_4, LED_4_NUMBER);
    } else {
        ClearBit(PORT_LED_4, LED_4_NUMBER);
    }

}

    
/**
 función principal
*/
int main() {
//    uint8_t sensores[MAX_SENSORES] = {0, 0, 0, 0};
    
    //valor_p = (sensores[S1] * 8 + sensores[S2] * 4 + sensores[S3] * 2 + sensores[S4]) / 
    //          ((sensores[S1] >> 5) + (sensores[S2] >> 5) + (sensores[S3] >> 5) + (sensores[S4] >> 5))
    
    startup();

    while (1) {
        motores_off();

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON2_NO_APRETADO) {
            mostrar_sensor_en_leds(S1);
        }
        _delay_ms(50); //rebote botón

        while (BOTON2_APRETADO);
        _delay_ms(5); //rebote botón

        // aceleración inicial gradual
        motor1_velocidad(50);
        motor2_velocidad(50);
        motores_on();
        _delay_ms(50);
        
        while (BOTON2_NO_APRETADO) {
            //obtener_sensores(sensores);
            //valor_p = sensores[0]
            //sensores = sensores + 20000;
        }

        // fin de tareas, para poder empezar de nuevo
        motores_off();
        _delay_ms(50); //rebote botón

        while (BOTON2_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}

