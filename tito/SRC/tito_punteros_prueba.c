#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"
#include <avr/pgmspace.h>

void mover_motor_izquierda() {
    PWM1_VEL(0);
    PWM2_VEL(100);
}

void mover_motor_derecha() {
    PWM1_VEL(100);
    PWM2_VEL(0);
}

/**
 función principal
*/
int main() {
    void (*funciones)(void *)[] = {&mover_motor_izquierda, &mover_motor_derecha};
    mot1_sent(AD);
    mot2_sent(AD);
    while (1) {
        _delay_ms(2000);
        funciones[0]();
        _delay_ms(2000);
        funciones[1]();
    }
}
