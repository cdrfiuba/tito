#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"
#include <avr/pgmspace.h>

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
    ClearBit (DDR_SENSOR_1, SENSOR_1_NUMBER);

    // botón
    ClearBit (DDR_BOTON, BOTON_NUMBER);
    SetBit (PORT_BOTON, BOTON_NUMBER);


    // PWM
    pwm_config();
    pwm_start();

    // pone el flag global para activar interrupciones
    sei();

    // establezco la dirección de los motores
    mot1_sent(AD);
    mot2_sent(AD);

}

/**
 función principal
*/
int main() {
    //int estado_actual;
    //int nuevo_estado;
    unsigned int estado_sensores = 0;
    uint16_t acumulador_izquierda = 0;
    uint16_t acumulador_derecha = 0;
    int control_acumulador_izquierda = 0;
    int control_acumulador_derecha = 0;
    int motor_vel_1 = 0;
    int motor_vel_2 = 0;
    
    startup();

    while (1) {
        PWM1_VEL(0);
        PWM2_VEL(0);

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON_NO_APRETADO);
        _delay_ms(50); //rebote botón
        

        while (BOTON_APRETADO);
        _delay_ms(5); //rebote botón

        // aceleración inicial gradual
        PWM1_VEL(5);
        PWM2_VEL(5);
        _delay_ms(50);

        PWM1_VEL(10);
        PWM2_VEL(10);
        _delay_ms(50);
        
        while (BOTON_NO_APRETADO) {
            // flags para empezar a acumular
            if ((SENSOR_4) && (!control_acumulador_izquierda)) {
                acumulador_izquierda = 0;
                control_acumulador_izquierda = 1;
            } else if ((SENSOR_2) && (control_acumulador_izquierda)) {
                acumulador_izquierda = 0;
                control_acumulador_izquierda = 0;
            }
            if ((SENSOR_1) && (!control_acumulador_derecha)) {
                acumulador_derecha = 0;
                control_acumulador_derecha = 1;
            } else if ((SENSOR_3) && (control_acumulador_derecha)) {
                acumulador_derecha = 0;
                control_acumulador_derecha = 0;
            }

            // término "integrativo" para compensar el proporcional, con control de overflow
            if ((control_acumulador_izquierda) && (acumulador_izquierda < 0x00FF)) {
                acumulador_izquierda++;
                mot1_sent(AD);
                mot2_sent(AT);
            } else if ((control_acumulador_derecha) && (acumulador_derecha < 0x00FF)) {
                acumulador_derecha++;
                mot1_sent(AT);
                mot2_sent(AD);
            }
            
            // términos proporcionales
            estado_sensores = 10;
            if ((SENSOR_1)) estado_sensores -= 10;
            if ((SENSOR_2)) estado_sensores += 15;
            if ((SENSOR_3)) estado_sensores += 30;
            if ((SENSOR_4)) estado_sensores += 60;
            //estado_sensores = ((SENSOR_1) * 00 + (SENSOR_2) * 15 + (SENSOR_3) * 30 + (SENSOR_4) * 45) / 
            //                  ((SENSOR_1) + (SENSOR_2) + (SENSOR_3) + (SENSOR_4));
            motor_vel_2 = estado_sensores / 2 + acumulador_izquierda / (1 << 2);
            PWM2_VEL(motor_vel_2);

            estado_sensores = 10;
            if ((SENSOR_1)) estado_sensores += 60;
            if ((SENSOR_2)) estado_sensores += 30;
            if ((SENSOR_3)) estado_sensores += 15;
            if ((SENSOR_4)) estado_sensores -= 10;
            //estado_sensores = ((SENSOR_1) * 45 + (SENSOR_2) * 30 + (SENSOR_3) * 15 + (SENSOR_4) * 00) / 
            //                  ((SENSOR_1) + (SENSOR_2) + (SENSOR_3) + (SENSOR_4));
            motor_vel_1 = estado_sensores / 2 + acumulador_derecha / (1 << 2);
            PWM1_VEL(motor_vel_1);
            
            /*if (acumulador_derecha == 0x00FF) {
                PWM1_VEL(40);
                PWM2_VEL(40);
            } else {
                PWM1_VEL(0);
                PWM2_VEL(0);
            }*/
            
            

        }

        // fin de tareas, para poder empezar de nuevo
        PWM1_VEL(0);
        PWM2_VEL(0);
        _delay_ms(50); //rebote botón

        estado_sensores = 0;
        acumulador_izquierda = 0;
        acumulador_derecha = 0;
        control_acumulador_izquierda = 0;
        control_acumulador_derecha = 0;

        while (BOTON_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}
