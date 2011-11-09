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
    int (*fn)(void *);
} tTransition;

/**
 handlers de eventos
 */
static int st_en_linea () {
    printf("st_en_linea \n");
    return ST_EN_LINEA;
};

static int st_yendose_poco_por_derecha () {
    printf("st_yendose_poco_por_derecha \n");
    return ST_YENDOSE_POCO_POR_DERECHA;
};
static int st_yendose_mucho_por_derecha () {
    printf("st_yendose_mucho_por_derecha \n");
    return ST_YENDOSE_MUCHO_POR_DERECHA;
};
static int st_afuera_por_derecha () {
    printf("st_afuera_por_derecha \n");
    return ST_AFUERA_POR_DERECHA;
};
static int st_volviendo_por_derecha () {
    printf("st_volviendo_por_derecha \n");
    return ST_VOLVIENDO_POR_DERECHA;
};
static int st_volvio_por_derecha () {
    printf("st_volvio_por_derecha \n");
    return ST_VOLVIO_POR_DERECHA;
};

static int st_yendose_poco_por_izquierda () {
    printf("st_yendose_poco_por_izquierda \n");
    return ST_YENDOSE_POCO_POR_IZQUIERDA;
};
static int st_yendose_mucho_por_izquierda () {
    printf("st_yendose_mucho_por_izquierda \n");
    return ST_YENDOSE_MUCHO_POR_IZQUIERDA;
};
static int st_afuera_por_izquierda () {
    printf("st_afuera_por_izquierda \n");
    return ST_AFUERA_POR_IZQUIERDA;
};
static int st_volviendo_por_izquierda () {
    printf("st_volviendo_por_izquierda \n");
    return ST_VOLVIENDO_POR_IZQUIERDA;
};
static int st_volvio_por_izquierda () {
    printf("st_volvio_por_izquierda \n");
    return ST_VOLVIO_POR_IZQUIERDA;
};

static int mantener_estado (int estado_actual) {
	// esto permite que un estado se llame a sí mismo
	printf("mantiene estado \n");
	return estado_actual;
};

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

	// acá se definen las transiciones de la fsm:
	// esencialmente esto ES la fsm
	tTransition trans[] = {
		{ST_EN_LINEA, EV_SENSORES_BNN, &st_yendose_mucho_por_derecha},
		{ST_EN_LINEA, EV_SENSORES_BBN, &st_yendose_poco_por_derecha},
		{ST_EN_LINEA, EV_SENSORES_NNB, &st_yendose_mucho_por_izquierda},
		{ST_EN_LINEA, EV_SENSORES_NBB, &st_yendose_poco_por_izquierda},
		{ST_EN_LINEA, EV_CUALQUIERA, &st_en_linea},

		{ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_NBN, &st_en_linea},
		{ST_YENDOSE_POCO_POR_DERECHA, EV_SENSORES_BNN, &st_yendose_mucho_por_derecha},
		{ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_BBN, &st_volvio_por_derecha},
		{ST_YENDOSE_MUCHO_POR_DERECHA, EV_SENSORES_NNN, &st_afuera_por_derecha},
		{ST_AFUERA_POR_DERECHA, EV_SENSORES_BNN, &st_volviendo_por_derecha},
		{ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NBN, &st_en_linea},
		{ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_BBN, &st_volvio_por_derecha},
		{ST_VOLVIENDO_POR_DERECHA, EV_SENSORES_NNN, &st_afuera_por_derecha},
		{ST_VOLVIO_POR_DERECHA, EV_SENSORES_NBN, &st_en_linea},
		{ST_VOLVIO_POR_DERECHA, EV_SENSORES_BNN, &st_yendose_mucho_por_derecha},

		{ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NBN, &st_en_linea},
		{ST_YENDOSE_POCO_POR_IZQUIERDA, EV_SENSORES_NNB, &st_yendose_mucho_por_izquierda},
		{ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NBB, &st_volvio_por_izquierda},
		{ST_YENDOSE_MUCHO_POR_IZQUIERDA, EV_SENSORES_NNN, &st_afuera_por_izquierda},
		{ST_AFUERA_POR_IZQUIERDA, EV_SENSORES_NNB, &st_volviendo_por_izquierda},
		{ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBN, &st_en_linea},
		{ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NBB, &st_volvio_por_izquierda},
		{ST_VOLVIENDO_POR_IZQUIERDA, EV_SENSORES_NNN, &st_afuera_por_izquierda},
		{ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NBN, &st_en_linea},
		{ST_VOLVIO_POR_IZQUIERDA, EV_SENSORES_NNB, &st_yendose_mucho_por_izquierda},

		{ST_CUALQUIERA, EV_CUALQUIERA, (void *)&mantener_estado} // transición default
	};
	#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))

	// Ciclo principal de la fsm:
	// no debería cambiarse, idealmente
	while (1) { // si se quiere que la fsm termine, se usa (state != ST_FIN)
		event = obtener_evento(); // obtiene el evento a procesar
		/* debug */ if (event != VALOR_INVALIDO) { /* debug */
		// cicla por todas las transiciones, y busca la que coincida con el
		// estado y evento actuales
		for (i = 0; i < TRANS_COUNT; i++) {
			if ((state == trans[i].st) || (ST_CUALQUIERA == trans[i].st)) {
				if ((event == trans[i].ev) || (EV_CUALQUIERA == trans[i].ev)) {
					// llama a la función encargada de manejar el evento,
					// y devolver el nuevo estado
					state = (trans[i].fn)((void *) state);
					break;
				}
			}
		}
		/* debug */ } /* debug */
	}
	return 1;
}

int obtener_estado_sensores(void) {
	int c = 0;

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


