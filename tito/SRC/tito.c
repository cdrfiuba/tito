#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tito.h"

int main(void) {
    for (;;) {
        PORT_LED_1 = 1;
        _delay_ms(1000);
        PORTC = 0;
        _delay_ms(1000);
    }
}
