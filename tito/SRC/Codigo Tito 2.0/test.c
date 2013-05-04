#include <stdio.h>
#include "test.h"

/**
 estructura para transiciones:
 determina el flujo de la fsm, es decir,
 qué eventos están permitidos para qué estados,
 y cuál es la función encargada de manejar ese estado.
*/
typedef struct {
    int st;
    int ev;
    int st_new;
} tTransition;

/**
 handlers de eventos
 */
int manejar_estado(int estado) {
    #define FACTOR 1 // coeficiente de disminuición de velocidad
    switch (estado) {
        case ST_EN_LINEA:
            printf("ST_EN_LINEA \n");
            break;


        case ST_YENDOSE_POCO_POR_DERECHA:
            printf("ST_YENDOSE_POCO_POR_DERECHA \n");
            break;

        case ST_YENDOSE_MUCHO_POR_DERECHA:
            printf("ST_YENDOSE_MUCHO_POR_DERECHA \n");
            break;

        case ST_AFUERA_POR_DERECHA:
            printf("ST_AFUERA_POR_DERECHA \n");
            break;

        case ST_VOLVIENDO_POR_DERECHA:
            printf("ST_VOLVIENDO_POR_DERECHA \n");
            break;

        case ST_VOLVIO_POR_DERECHA:
            printf("ST_VOLVIO_POR_DERECHA \n");
            break;


        case ST_YENDOSE_POCO_POR_IZQUIERDA:
            printf("ST_YENDOSE_POCO_POR_IZQUIERDA \n");
            break;

        case ST_YENDOSE_MUCHO_POR_IZQUIERDA:
            printf("ST_YENDOSE_MUCHO_POR_IZQUIERDA \n");
            break;

        case ST_AFUERA_POR_IZQUIERDA:
            printf("ST_AFUERA_POR_IZQUIERDA \n");
            break;

        case ST_VOLVIENDO_POR_IZQUIERDA:
            printf("ST_VOLVIENDO_POR_IZQUIERDA \n");
            break;

        case ST_VOLVIO_POR_IZQUIERDA:
            printf("ST_VOLVIO_POR_IZQUIERDA \n");
            break;
    }
    return estado;
}

/**
 Función principal para la fsm, se encarga de devolver
 el evento que corresponde.
 Si se quisiera implementar una cola de eventos,
 esta función sería la responsable de manejarla.
*/
int obtener_evento(void) {
    return obtener_estado_sensores();
}

/**
 función principal
*/
int main() {

    int i = 0;

    // declaro "state" y "event" en vez de "estado" y "evento"
    // porque se distinguen más entre sí
    int state = ST_EN_LINEA;
    int event = EV_CUALQUIERA;
    printf("sizeof int: %i \n", sizeof(int));


    // acá se definen las transiciones de la fsm:
    // esencialmente esto ES la fsm
    tTransition trans[] = {
        {ST_EN_LINEA, EV_SENSORES_BNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_BBN, ST_YENDOSE_POCO_POR_DERECHA},
        {ST_EN_LINEA, EV_SENSORES_NNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_EN_LINEA, EV_SENSORES_NBB, ST_YENDOSE_POCO_POR_IZQUIERDA},

        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_BNN, ST_YENDOSE_MUCHO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_BBN, ST_VOLVIO_POR_DERECHA},
        {ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNN, ST_AFUERA_POR_DERECHA},
        {ST_AFUERA_POR_DERECHA, EV_SENSORES_BNN, ST_VOLVIENDO_POR_DERECHA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NBN, ST_EN_LINEA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_BBN, ST_VOLVIO_POR_DERECHA},
        {ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NNN, ST_AFUERA_POR_DERECHA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_NBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_DERECHA, EV_SENSORES_BNN, ST_YENDOSE_MUCHO_POR_DERECHA},

        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NBN, ST_EN_LINEA},
        {ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NBB, ST_VOLVIO_POR_IZQUIERDA},
        {ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NNN, ST_AFUERA_POR_IZQUIERDA},
        {ST_AFUERA_POR_IZQUIERDA, EV_SENSORES_NNB, ST_VOLVIENDO_POR_IZQUIERDA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBN, ST_EN_LINEA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBB, ST_VOLVIO_POR_IZQUIERDA},
        {ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NNN, ST_AFUERA_POR_IZQUIERDA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NBN, ST_EN_LINEA},
        {ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NNB, ST_YENDOSE_MUCHO_POR_IZQUIERDA},

        {ST_MAX, EV_CUALQUIERA, ST_MAX} // transición máxima
    };
    #define TRANS_COUNT (sizeof(trans)/sizeof(*trans))
    #define len(array) (sizeof(array)/sizeof(*array))

    int trans_count = 0;
    printf("trans[0] = %i \n", trans[0].st);
    printf("ST_MAX = %i \n", ST_MAX);
    for (i = 0; ; i++) {
        printf("i = %i \n", i);
        trans_count = i + 1;
        if (ST_MAX == trans[i].st) {
            break;
        }
    }
    printf("trans_count = %i \n", trans_count);
    printf("len(trans) = %i \n", len(trans));


    printf("ST_EN_LINEA \n");
    // Ciclo principal de la fsm:
    // no debería cambiarse, idealmente
    while (1) { // si se quiere que la fsm termine, se usa (state != ST_FIN)
        event = obtener_evento(); // obtiene el evento a procesar
        //printf("evento %i \n", event);
        /* debug */ if (event != VALOR_INVALIDO) { /* debug */
        // cicla por todas las transiciones, y busca la que coincida con el
        // estado y evento actuales
        for (i = 0; i < len(trans); i++) {
            printf("i = %i, st = %i, ev = %i, st_new = %i \n", i, trans[i].st, trans[i].ev, trans[i].st_new);
            if ((state == trans[i].st) && (event == trans[i].ev)) {
                    // llama a la función encargada de
                    // manejar el estado actual y devolver el nuevo estado
                    printf("state %i \n", trans[i].st);
                    printf("event %i \n", trans[i].ev);
                    printf("state new %i \n", trans[i].st_new);
                    state = manejar_estado(trans[i].st_new);
                    printf("state output %i \n", state);
                    break;
            }
        }
        if (i > 24) {
            printf("desbordamiento \n");
        }

        /* debug */ } /* debug */
    }
    return 1;
}

int obtener_estado_sensores(void) {
    int c = 0;

    printf("\ningrese nuevo estado(0-8):");
    // obtengo caracteres del input
    c = getchar();

    // si es un número,
    // entonces devuelvo el número, calculado como
    // (valor_ascii - valor_ascii_numero_0)
    // si no, devuelvo -1
    if (c >= ASCII_0 && c <= ASCII_9) {
        return c - ASCII_0;
    } else {
        return VALOR_INVALIDO;
    }
}


