//#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tito.h"
#include "lib/motores.h"
#include "lib/common.h"
#include "lib/usart.c"
#include <stdio.h>

int usart_putchar_printf(char var, FILE *stream) {
    if (var == '\n') USART0Transmit('\r');
    USART0Transmit(var);
    return 0;
}

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

inline void setear_conversor_ad(uint8_t sensor){
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)); 
    ADMUX |= sensor; 
}
void configurar_adc(void) {
    ADMUX = ( (0 << REFS1) | (1 << REFS0) | (1 << ADLAR) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) );
    ADCSRA = ( (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIE)  | (0 << ADPS2) | (0 << ADPS1)| (0 << ADPS0) );
    ADCSRB = ( (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0) | (0 << ACME) );
}

void startup () {
// setear puertos de lectura o escritura,
// según corresponda

    stdout = &mystdout;

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
    configurar_adc();
    
    // inicialización de puerto serie
    USART0Setup(USART_BAUDRATE, USART0_CHARSIZE_8BIT, USART0_STOP_1BIT, USART0_PARITY_DIS, USART0_MODE_ASYNC);
    _delay_ms(10);

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
        setear_conversor_ad (i);
        iniciar_conversion_ad();
        while(CONVIRTIENDO_AD);
        sensores[i] = LEER_CONVERSION_AD;
    }
}


void mostrar_sensor_en_leds (uint8_t sensor) {
    uint8_t sensores[MAX_SENSORES] = {0, 0, 0, 0};
    obtener_sensores(sensores);

    if (IsBitSet(sensores[sensor], 7)) {
        SetBit(PORT_LED_1, LED_1_NUMBER);
    } else {
        ClearBit(PORT_LED_1, LED_1_NUMBER);
    }
    if (IsBitSet(sensores[sensor], 6)) {
        SetBit(PORT_LED_2, LED_2_NUMBER);
    } else {
        ClearBit(PORT_LED_2, LED_2_NUMBER);
    }
    if (IsBitSet(sensores[sensor], 5)) {
        SetBit(PORT_LED_3, LED_3_NUMBER);
    } else {
        ClearBit(PORT_LED_3, LED_3_NUMBER);
    }
    if (IsBitSet(sensores[sensor], 4)) {
        SetBit(PORT_LED_4, LED_4_NUMBER);
    } else {
        ClearBit(PORT_LED_4, LED_4_NUMBER);
    }
    //USART0Transmit('S');
    //_delay_ms(100);
}

    
/**
 función principal
*/
int main() {
    uint8_t sensores[MAX_SENSORES] = {0, 0, 0, 0};
    int16_t sensores_linea = 0;
    int16_t err_p = 0;
    int16_t err_p_anterior = 0;
    int16_t err_d = 0;
    int32_t err_i = 0;
    int8_t dif_potencia = 0;
    
    startup();

    while (1) {
        motores_off();

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON2_NO_APRETADO) {
            //mostrar_sensor_en_leds(S2);
        }
        _delay_ms(50); //rebote botón

        while (BOTON2_APRETADO);
        _delay_ms(5); //rebote botón

        // aceleración inicial gradual
        motor1_velocidad(20);
        motor2_velocidad(20);
        motores_on();
        _delay_ms(50);
        
        while (BOTON2_NO_APRETADO) {
            obtener_sensores(sensores);
            sensores_linea = ((int32_t)sensores[S2] * 1000 + (int32_t)sensores[S3] * 2000 + (int32_t)sensores[S4] * 3000) / 
                             ( (int32_t)sensores[S1] + (int32_t)sensores[S2] + (int32_t)sensores[S3] + (int32_t)sensores[S4] );
             

            //printf("%10lu, %10lu\n", 
            //    (int32_t)sensores[S2] * 1000 + (int32_t)sensores[S3] * 2000 + (int32_t)sensores[S4] * 3000, 
            //    (int32_t)sensores[S1] + (int32_t)sensores[S2] + (int32_t)sensores[S3] + (int32_t)sensores[S4]);
            //printf("%10i (%3d, %3d, %3d, %3d)\n", sensores_linea, sensores[S1], sensores[S2], sensores[S3], sensores[S4]);

            err_p = sensores_linea - 1500;
            err_d = err_p - err_p_anterior;
            err_i += err_p;
            /*if ( (err_i >= VALOR_MAX_INT32 - VALOR_MAX_INT16) || (err_i <= -(VALOR_MAX_INT32 - VALOR_MAX_INT16)) ) {
                err_i -= err_p;
            }*/
            err_p_anterior = err_p;

            //printf("%10i, %10li, %10i\n", err_p, err_i, err_d);

            dif_potencia = err_p / 20 + /*err_i / 10000 + */ err_d * 3 / 2;
 
            if (dif_potencia > MAX_VELOCIDAD) {
                dif_potencia = MAX_VELOCIDAD;
            }
            if (dif_potencia < -MAX_VELOCIDAD) {
                dif_potencia = -MAX_VELOCIDAD;
            }
             
            //printf("%10i\n", dif_potencia);
            
            if (dif_potencia < 0) {
                motor1_velocidad_pid(MAX_VELOCIDAD + dif_potencia + 127);
                motor2_velocidad_pid(MAX_VELOCIDAD + 127);
            } else {
                motor1_velocidad_pid(MAX_VELOCIDAD + 127);
                motor2_velocidad_pid(MAX_VELOCIDAD - dif_potencia + 127);
            }
            
            //if (dif_potencia < 0) {
            //    printf("motores %3i, %3i\n", MAX_VELOCIDAD + dif_potencia, MAX_VELOCIDAD);
            //} else {
            //    printf("motores %3i, %3i\n", MAX_VELOCIDAD, MAX_VELOCIDAD - dif_potencia);
            //}
        }

        // fin de tareas, para poder empezar de nuevo
        motores_off();
        _delay_ms(50); //rebote botón

        while (BOTON2_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}

