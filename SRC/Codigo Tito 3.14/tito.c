//#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tito.h"
#include "lib/motores.h"
#include "lib/common.h"
#include "lib/usart.c"
#include <stdio.h>

volatile uint8_t tolerancia = 30;

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
}

inline void mostrar_leds(uint8_t *sensores) {
    //static uint8_t boton_apretado = 0;

    //while (BOTON1_APRETADO) {
        //boton_apretado = 1;
    //}
    //_delay_ms(5); //rebote botón
    //if (boton_apretado == 1) {
        //tolerancia = tolerancia + 5;
        //if (tolerancia == 180) {
            //tolerancia = 0;
        //}
        //boton_apretado = 0;
    //}

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

    // printf("%3d %3d %3d %3d %3d %3d\n", sensores[S1], sensores[S2], sensores[S3], sensores[S4], sensores[S5], sensores[S6]);

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
    int8_t coeficiente_error_p = 14;
    int16_t coeficiente_error_i = 12016;
    int8_t coeficiente_error_d = 6;
    int8_t tipo_coeficiente = 0; // de 0 a 15
    int16_t gusty1 = 0;
    int16_t gusty2 = 0;
    int16_t gusty3 = 0;
    startup();
        
    while (1) {
        motores_off();
        ClearBit(PORT_LED_1, LED_1_NUMBER);
        ClearBit(PORT_LED_2, LED_2_NUMBER);
        ClearBit(PORT_LED_3, LED_3_NUMBER);
        ClearBit(PORT_LED_4, LED_4_NUMBER);
        
        // cambios de coeficientes
        if (tipo_coeficiente == 16) {
            tipo_coeficiente = 0;
        }

        switch (tipo_coeficiente) {
            case 0:
                // valor de referencia
                coeficiente_error_p = 14;
                coeficiente_error_i = 240;
                coeficiente_error_d = 2;
                break;
            case 1:
                coeficiente_error_p = 14;
                coeficiente_error_i = 12016;
                coeficiente_error_d = 12;
                break;
            case 2:
                coeficiente_error_p = 14;
                coeficiente_error_i = 12016;
                coeficiente_error_d = 24;
                break;
            case 3:
                coeficiente_error_p = 14;
                coeficiente_error_i = 12016;
                coeficiente_error_d = 48;
                break;
            case 4:
                coeficiente_error_p = 14;
                coeficiente_error_i = 12016;
                coeficiente_error_d = 96;
                break;
            case 5:
                coeficiente_error_p = 14;
                coeficiente_error_i = 12016;
                coeficiente_error_d = 192;
                break;
            case 6:
                coeficiente_error_p = 14;
                coeficiente_error_i = 12016;
                coeficiente_error_d = 6;
                break;
            case 7:
                coeficiente_error_p = 14;
                coeficiente_error_i = 6000;
                coeficiente_error_d = 6;
                break;
            case 8:
                coeficiente_error_p = 14;
                coeficiente_error_i = 3000;
                coeficiente_error_d = 6;
                break;
            case 9:
                coeficiente_error_p = 14;
                coeficiente_error_i = 1500;
                coeficiente_error_d = 6;
                break;
            case 10:
                coeficiente_error_p = 14;
                coeficiente_error_i = 750;
                coeficiente_error_d = 6;
                break;
            case 11:
                coeficiente_error_p = 14;
                coeficiente_error_i = 375;
                coeficiente_error_d = 6;
                break;
            case 12:
                coeficiente_error_p = 14;
                coeficiente_error_i = 200;
                coeficiente_error_d = 6;
                break;
            case 13:
                coeficiente_error_p = 14;
                coeficiente_error_i = 100;
                coeficiente_error_d = 6;
                break;
            case 14:
                coeficiente_error_p = 14;
                coeficiente_error_i = 50;
                coeficiente_error_d = 6;
                break;
            case 15:
                coeficiente_error_p = 14;
                coeficiente_error_i = 25;
                coeficiente_error_d = 6;
                break;
        }
        if (tipo_coeficiente & (1 << 0)) {
            SetBit(PORT_LED_1, LED_1_NUMBER);
        }
        if (tipo_coeficiente & (1 << 1)) {
            SetBit(PORT_LED_2, LED_2_NUMBER);
        }
        if (tipo_coeficiente & (1 << 2)) {
            SetBit(PORT_LED_3, LED_3_NUMBER);
        }
        if (tipo_coeficiente & (1 << 3)) {
            SetBit(PORT_LED_4, LED_4_NUMBER);
        }
        tipo_coeficiente++;

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON2_NO_APRETADO) {
            //mostrar_sensor_en_leds(S2);
            //obtener_sensores(sensores);
            //mostrar_leds(sensores);
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
        _delay_ms(DELAY_ARRANQUE);
        motor1_velocidad(20);
        motor2_velocidad(20);
        _delay_ms(DELAY_ARRANQUE);
        motor1_velocidad(35);
        motor2_velocidad(35);
        _delay_ms(DELAY_ARRANQUE);
        motor1_velocidad(50);
        motor2_velocidad(50);
        _delay_ms(DELAY_ARRANQUE);
        motor1_velocidad(65);
        motor2_velocidad(65);
        _delay_ms(DELAY_ARRANQUE);
        motor1_velocidad(80);
        motor2_velocidad(80);
        _delay_ms(DELAY_ARRANQUE);
        
        while (BOTON2_NO_APRETADO) {
            obtener_sensores(sensores);

            if (sensores[S1] > 50) {
                ultimo_borde_valido = BORDE_IZQUIERDA;
            } else if (sensores[S6] > 50) {
                ultimo_borde_valido = BORDE_DERECHA;
            }
            
            // si me fui, entro en modo "corrección máxima"
            if ( (sensores[S1] < tolerancia) && (sensores[S2] < tolerancia) && (sensores[S3] < tolerancia) && (sensores[S4] < tolerancia) && (sensores[S5] < tolerancia) && (sensores[S6] < tolerancia) ) {
                estado_actual = ST_AFUERA;
            } else {
                estado_actual = ST_EN_PISTA;
                //ClearBit(PORT_LED_1, LED_1_NUMBER);
                //ClearBit(PORT_LED_2, LED_2_NUMBER);
                //ClearBit(PORT_LED_3, LED_3_NUMBER);
                //ClearBit(PORT_LED_4, LED_4_NUMBER);
            }

            switch (estado_actual) {
                case ST_EN_PISTA:
                    // 6 sensores
                    sensores_linea = ((int32_t)sensores[S2] * 1000 + (int32_t)sensores[S3] * 2000 + (int32_t)sensores[S4] * 3000 + (int32_t)sensores[S5] * 4000 + (int32_t)sensores[S6] * 5000) / 
                                     ( (int32_t)sensores[S1] + (int32_t)sensores[S2] + (int32_t)sensores[S3] + (int32_t)sensores[S4] + (int32_t)sensores[S5] + (int32_t)sensores[S6] );

                    err_p = sensores_linea - CENTRO_DE_LINEA;
                    err_d = err_p - err_p_anterior;
                    err_i += (err_p >> 8);
                    if ( (err_i >= VALOR_MAX_INT16 - VALOR_MAX_ERR_P) || (err_i <= -(VALOR_MAX_INT16 - VALOR_MAX_ERR_P)) ) {
                        err_i -= (err_p >> 8);
                    }
                    err_p_anterior = err_p;
                    
                    reduccion_velocidad = 0;
                    //if (coeficiente_error_p > 0) {
                        //reduccion_velocidad += err_p / coeficiente_error_p;
                    //}
                    //if (coeficiente_error_i > 0) {
                        //reduccion_velocidad += err_i / coeficiente_error_i;
                    //}
                    //if (coeficiente_error_d > 0) {
                        //reduccion_velocidad += err_d / coeficiente_error_d;
                    //}
                    
                    gusty1=err_p/coeficiente_error_p;
                    gusty2=err_i/coeficiente_error_i;
                    gusty3=err_d/coeficiente_error_d;
                    
                    //if (gusty3 > RANGO_VELOCIDAD){
                        //SetBit(PORT_LED_1, LED_1_NUMBER);
                        //SetBit(PORT_LED_2, LED_2_NUMBER);
                    //}else{
                        //ClearBit(PORT_LED_1, LED_1_NUMBER);
                        //ClearBit(PORT_LED_2, LED_2_NUMBER);
                    //}    
                     
                    //if (gusty3 < -RANGO_VELOCIDAD){
                        //SetBit(PORT_LED_3, LED_3_NUMBER);
                        //SetBit(PORT_LED_4, LED_4_NUMBER);
                    //}else{
                        //ClearBit(PORT_LED_3, LED_3_NUMBER);
                        //ClearBit(PORT_LED_4, LED_4_NUMBER);
                    //}   
                    
                    reduccion_velocidad = gusty1 + gusty2 + gusty3;
                            
                    //reduccion_velocidad = err_p / coeficiente_error_p + err_i / coeficiente_error_i + err_d / coeficiente_error_d;
                    
                    // printf de valores PID
                    //printf("p:%5i i:%5i d:%5i rv:%5i\n", err_p, err_i, err_d, reduccion_velocidad);

                    // err_p toma valores entre -2500 y 2500, por lo reduccion_velocidad esta acotado entre -125 y +125 
                    // err_i toma valores entre -32k y 32k, por lo que su aporte a diff_potencia esta acotado entre -32 y +32 (-32 y +32 para 6 sensores)
                    // err_d toma valores entre -5k y 5k, por lo que su aporte a diff_potencia esta acotado entre -inf y +inf (para los niveles de representacion que manejamos). 
                    // Para un caso normal, en que err_p varie 30 entre una medicion y la siguiente, estará acotado entre -45 y +45
                    
                    if (reduccion_velocidad > RANGO_VELOCIDAD) {
                        reduccion_velocidad = RANGO_VELOCIDAD;
                        
                    } else if (reduccion_velocidad < -RANGO_VELOCIDAD) {
                        reduccion_velocidad = -RANGO_VELOCIDAD;
                    }
                                 
                    if (reduccion_velocidad < 0) {
                        motor1_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD / 2 - reduccion_velocidad / 2);
                        motor2_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD / 2 + reduccion_velocidad / 2);
                    } else {
                        motor1_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD / 2 - reduccion_velocidad / 2);
                        motor2_velocidad_pid(MIN_VELOCIDAD + RANGO_VELOCIDAD / 2 + reduccion_velocidad / 2);
                    }
                    
                    break;
                    
                case ST_AFUERA:
                    if (ultimo_borde_valido == BORDE_IZQUIERDA) {
                        //printf("Todo afuera por izquierda\n");
                        motor1_velocidad_pid(MIN_VELOCIDAD + 20);
                        motor2_velocidad_pid(MIN_VELOCIDAD);
                        SetBit(PORT_LED_2, LED_2_NUMBER);
                    } else if (ultimo_borde_valido == BORDE_DERECHA) {
                        //printf("Todo afuera por derecha\n");
                        motor1_velocidad_pid(MIN_VELOCIDAD);
                        motor2_velocidad_pid(MIN_VELOCIDAD + 20);
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

