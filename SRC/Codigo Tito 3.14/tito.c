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
    uint8_t sensores[MAX_SENSORES] = MAX_SENSORES_INIT;
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

inline void mostrar_leds(uint8_t *sensores) {
    static uint8_t tolerancia = 180;
    static uint8_t boton_apretado = 0;

    while (BOTON1_APRETADO) {
        boton_apretado = 1;
    }
    _delay_ms(5); //rebote botón
    if (boton_apretado == 1) {
        tolerancia = tolerancia - 5;
        if (tolerancia == 0) {
            tolerancia = 180;
        }
        boton_apretado = 0;
    }        

    if (sensores[S6] > tolerancia) {
        SetBit(PORT_LED_1, LED_1_NUMBER);
    } else {
        ClearBit(PORT_LED_1, LED_1_NUMBER);
    }
    if ( (sensores[S5] > tolerancia) && (sensores[S4] > tolerancia) ) {
        SetBit(PORT_LED_2, LED_2_NUMBER);
    } else {
        ClearBit(PORT_LED_2, LED_2_NUMBER);
    }
    if ( (sensores[S3] > tolerancia) && (sensores[S2] > tolerancia) ) {
        SetBit(PORT_LED_3, LED_3_NUMBER);
    } else {
        ClearBit(PORT_LED_3, LED_3_NUMBER);
    }
    if (sensores[S1] > tolerancia) {
        SetBit(PORT_LED_4, LED_4_NUMBER);
    } else {
        ClearBit(PORT_LED_4, LED_4_NUMBER);
    }

    /*if (sensores[3] > tolerancia) {
        SetBit(PORT_LED_1, LED_1_NUMBER);
    } else {
        ClearBit(PORT_LED_1, LED_1_NUMBER);
    }
    if (sensores[2] > tolerancia) {
        SetBit(PORT_LED_2, LED_2_NUMBER);
    } else {
        ClearBit(PORT_LED_2, LED_2_NUMBER);
    }
    if (sensores[1] > tolerancia) {
        SetBit(PORT_LED_3, LED_3_NUMBER);
    } else {
        ClearBit(PORT_LED_3, LED_3_NUMBER);
    }
    if (sensores[0] > tolerancia) {
        SetBit(PORT_LED_4, LED_4_NUMBER);
    } else {
        ClearBit(PORT_LED_4, LED_4_NUMBER);
    }*/
}

    
/**
 función principal
*/
int main() {
    uint8_t sensores[MAX_SENSORES] = MAX_SENSORES_INIT;
    int16_t sensores_linea = 0;
    int16_t err_p = 0;
    int16_t err_p_anterior = 0;
    int16_t err_d = 0;
    int16_t err_i = 0;
    int16_t reduccion_velocidad = 0;
    estados_t estado_actual = ST_EN_PISTA;
    bordes_t ultimo_borde_valido = BORDE_IZQUIERDA;
    //bordes_t ultimo_borde_valido_anterior = BORDE_IZQUIERDA;
    //bordes_t ultimo_borde_valido_nuevo = BORDE_IZQUIERDA;
    //uint8_t contador_ultimo_borde_valido = 0;
    
    startup();
    
    while (1) {
        motores_off();
        ClearBit(PORT_LED_1, LED_1_NUMBER);
        ClearBit(PORT_LED_2, LED_2_NUMBER);
        ClearBit(PORT_LED_3, LED_3_NUMBER);
        ClearBit(PORT_LED_4, LED_4_NUMBER);

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON2_NO_APRETADO) {
            //mostrar_sensor_en_leds(S2);
            obtener_sensores(sensores);
            mostrar_leds(sensores);
        }
        _delay_ms(50); //rebote botón

        while (BOTON2_APRETADO);
        _delay_ms(5); //rebote botón

        // inicialización
        err_p = 0;
        err_p_anterior = 0;
        err_d = 0;
        err_i = 0;
        estado_actual = ST_EN_PISTA;
        //contador_ultimo_borde_valido = 0;

        // aceleración inicial gradual

        motor1_velocidad(10);
        motor2_velocidad(10);
        motores_on();
        _delay_ms(100);
        motor1_velocidad(20);
        motor2_velocidad(20);
        _delay_ms(100);
        motor1_velocidad(35);
        motor2_velocidad(35);
        _delay_ms(100);
        motor1_velocidad(50);
        motor2_velocidad(50);
        _delay_ms(100);
        motor1_velocidad(65);
        motor2_velocidad(65);
        _delay_ms(100);
        motor1_velocidad(80);
        motor2_velocidad(80);
        _delay_ms(100);
        
        while (BOTON2_NO_APRETADO) {
            obtener_sensores(sensores);

            //printf("%3d, %3d, %3d, %3d\n", sensores[S1], sensores[S2], sensores[S3], sensores[S4]);
            //mostrar_leds(sensores);
            
            /*if (sensores[S1] > 100) {
                ultimo_borde_valido_nuevo = BORDE_IZQUIERDA;
            } else if (sensores[S6] > 100) {
                ultimo_borde_valido_nuevo = BORDE_DERECHA;
            }
            // promediar ultimas mediciones de "último borde válido"
            if (ultimo_borde_valido_nuevo == ultimo_borde_valido_anterior) {
                if (contador_ultimo_borde_valido >= 3) {
                    ultimo_borde_valido = ultimo_borde_valido_nuevo;
                } else {
                    contador_ultimo_borde_valido++;
                }
            } else {
                contador_ultimo_borde_valido = 0;
                ultimo_borde_valido_nuevo = ultimo_borde_valido_anterior;
            }*/

            if (sensores[S1] > 50) {
                ultimo_borde_valido = BORDE_IZQUIERDA;
            } else if (sensores[S6] > 50) {
                ultimo_borde_valido = BORDE_DERECHA;
            }
            
            // si me fui, entro en modo "corrección máxima"
            //if ( (sensores[S1] < 50) && (sensores[S2] < 50) && (sensores[S3] < 50) && (sensores[S4] < 50) ) {
            if ( (sensores[S1] < 30) && (sensores[S2] < 30) && (sensores[S3] < 30) && (sensores[S4] < 30) && (sensores[S5] < 30) && (sensores[S6] < 30) ) {
                //estado_actual = ST_AFUERA;
            } else {
                estado_actual = ST_EN_PISTA;
                ClearBit(PORT_LED_1, LED_1_NUMBER);
                ClearBit(PORT_LED_2, LED_2_NUMBER);
                ClearBit(PORT_LED_3, LED_3_NUMBER);
                ClearBit(PORT_LED_4, LED_4_NUMBER);
            }

            switch (estado_actual) {
                case ST_EN_PISTA:
                    // 4 sensores
                    //sensores_linea = ((int32_t)sensores[S2] * 1000 + (int32_t)sensores[S3] * 2000 + (int32_t)sensores[S4] * 3000) / 
                    //                 ( (int32_t)sensores[S1] + (int32_t)sensores[S2] + (int32_t)sensores[S3] + (int32_t)sensores[S4] );
                    // 6 sensores
                    sensores_linea = ((int32_t)sensores[S2] * 1000 + (int32_t)sensores[S3] * 2000 + (int32_t)sensores[S4] * 3000 + (int32_t)sensores[S5] * 4000 + (int32_t)sensores[S6] * 5000) / 
                                     ( (int32_t)sensores[S1] + (int32_t)sensores[S2] + (int32_t)sensores[S3] + (int32_t)sensores[S4] + (int32_t)sensores[S5] + (int32_t)sensores[S6] );

                    //printf("%10i (%3d, %3d, %3d, %3d)\n", sensores_linea, sensores[S1], sensores[S2], sensores[S3], sensores[S4]);

                    //err_p = sensores_linea - 1500;  //Con 4 sensores
                    err_p = sensores_linea - 2500; //Con 6 sensores
                    err_d = err_p - err_p_anterior;
                    err_i += err_p;
                    if ( (err_i >= VALOR_MAX_INT16 - VALOR_MAX_ERR_P) || (err_i <= -(VALOR_MAX_INT16 - VALOR_MAX_ERR_P)) ) {
                        err_i -= err_p;
                    }
                    err_p_anterior = err_p;

                    reduccion_velocidad = err_p * COEFICIENTE_ERROR_P /*+ err_i * COEFICIENTE_ERROR_I*/ + err_d * COEFICIENTE_ERROR_D;

                    // err_p toma valores entre -1500 y 1500, por lo 0000000000000000reduccion_velocidad esta acotado entre -75 y +75 (-125 y +125 para 6 sensores)
                    // err_i toma valores entre -32k y 32k, por lo que su aporte a diff_potencia esta acotado entre -32 y +32 (-32 y +32 para 6 sensores)
                    // err_d toma valores entre -5k y 5k, por lo que su aporte a diff_potencia esta acotado entre -inf y +inf (para los niveles de representacion que manejamos). Para un caso normal, en que err_p varie 30 entre una medicion y la siguiente, estará acotado entre -45 y +45
         
                    if (reduccion_velocidad > RANGO_VELOCIDAD) {
                        reduccion_velocidad = RANGO_VELOCIDAD;
                    } else if (reduccion_velocidad < -RANGO_VELOCIDAD) {
                        reduccion_velocidad = -RANGO_VELOCIDAD;
                    }
                                 
                    //printf("p:%10i, i:%10i, d:%10i, pot%10i\n", err_p, err_i, err_d, reduccion_velocidad);
                    
                    if (reduccion_velocidad < 0) {
                        motor1_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD/2 - reduccion_velocidad/2);
                        motor2_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD/2 + reduccion_velocidad/2);
                    } else {
                        motor1_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD/2 - reduccion_velocidad/2);
                        motor2_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD/2 + reduccion_velocidad/2);
                    }
                    
                    //if (reduccion_velocidad < 0) {
                    //    printf("motores %3i, %3i\n", MAX_VELOCIDAD + reduccion_velocidad, MAX_VELOCIDAD);
                    //} else {
                    //    printf("motores %3i, %3i\n", MAX_VELOCIDAD, MAX_VELOCIDAD - reduccion_velocidad);
                    //}
                    break;
                    
                case ST_AFUERA:
                    if (ultimo_borde_valido == BORDE_IZQUIERDA) {
                        //printf("Todo afuera por izquierda\n");
                        motor1_velocidad_pid(MIN_VELOCIDAD + 65);
                        motor2_velocidad_pid(MIN_VELOCIDAD);
                        SetBit(PORT_LED_2, LED_2_NUMBER);
                    } else if (ultimo_borde_valido == BORDE_DERECHA) {
                        //printf("Todo afuera por derecha\n");
                        motor1_velocidad_pid(MIN_VELOCIDAD);
                        motor2_velocidad_pid(MIN_VELOCIDAD + 65);
                        SetBit(PORT_LED_1, LED_1_NUMBER);
                        SetBit(PORT_LED_3, LED_3_NUMBER);
                        SetBit(PORT_LED_4, LED_4_NUMBER);
                    }
                    break;
            }    
        }

        // fin de tareas, para poder empezar de nuevo
        motores_off();
        _delay_ms(50); //rebote botón

        while (BOTON2_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}

