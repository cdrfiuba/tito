#ifndef _VELOCIDADES_H_
#define _VELOCIDADES_H_

#define FACTOR 1 // coeficiente de disminuición de velocidad

#define ESTADO_SENSORES ((SENSOR_IZQUIERDA_AFUERA << 3) | (SENSOR_IZQUIERDA_CENTRO << 2) | (SENSOR_DERECHA_CENTRO << 1) | (SENSOR_DERECHA_AFUERA))

// las velocidades van de -100 a 100, determinado en tito.h

// (MIN_VELOCIDAD + RANGO_VELOCIDAD) va de 0 a 255
#define RANGO_VELOCIDAD 100
#define MIN_VELOCIDAD 127 // si es <127, los motores van en reversa
#define BASE 50 // define cual es la velocidad que se le suma a MIN_VELOCIDAD en el caso que se este en linea
#define ESCALA_BAJA 2 // define que tan rapido satura la velocidad a MIN_VELOCIDAD para el motor que deseamos que vaya mas lento, valores mas grandes hacen que no se alcance la velocidad minima seguido
#define ESCALA_ALTA 2 // define que tan rapido satura la velocidad a MIN_VELOCIDAD para el motor que deseamos que vaya mas lento, valores mas pequeños hacen que la velocidad maxima se alcance mas seguido

#define COEFICIENTE_ERROR_P 1 / 14
#define COEFICIENTE_ERROR_I 1 / 12016
#define COEFICIENTE_ERROR_D 1 / 6

#define COEFICIENTE_DERECHA FACTOR * 0.9
#define COEFICIENTE_IZQUIERDA FACTOR * 0.9
#define USAR_CANCELACION_DE_INERCIA 1

/*	EN LINEA	*/
#define VELOCIDAD_IZQUIERDA_EL		80
#define VELOCIDAD_DERECHA_EL		80

/****	DERECHA	****/
/*	YENDOSE POCO POR DERECHA	*/
#define VELOCIDAD_IZQUIERDA_YPPD	60
#define VELOCIDAD_DERECHA_YPPD		80

/*	YENDOSE BASTANTE POR DERECHA	*/
#define VELOCIDAD_IZQUIERDA_YBPD	50
#define VELOCIDAD_DERECHA_YBPD		80

/*	YENDOSE MUCHO POR DERECHA	*/
#define VELOCIDAD_IZQUIERDA_YMPD	20
#define VELOCIDAD_DERECHA_YMPD		60

/*	AFUERA POR DERECHA	*/
#define VELOCIDAD_IZQUIERDA_APD		5
#define VELOCIDAD_DERECHA_APD		100

/*	VOLVIENDO POR DERECHA	*/
#define VELOCIDAD_IZQUIERDA_VEPD	30
#define VELOCIDAD_DERECHA_VEPD		60

/*	VOLVIO POR DERECHA	*/
//#define VELOCIDAD_IZQUIERDA_VOPD	60
//#define VELOCIDAD_DERECHA_VOPD		50


/****	IZQUIERDA	****/
/*	YENDOSE POCO POR IZQUIERDA	*/
#define VELOCIDAD_IZQUIERDA_YPPI	VELOCIDAD_DERECHA_YPPD
#define VELOCIDAD_DERECHA_YPPI		VELOCIDAD_IZQUIERDA_YPPD

/*	YENDOSE BASTANTE POR IZQUIERDA	*/
#define VELOCIDAD_IZQUIERDA_YBPI	VELOCIDAD_DERECHA_YBPD
#define VELOCIDAD_DERECHA_YBPI		VELOCIDAD_IZQUIERDA_YBPD

/*	YENDOSE MUCHO POR IZQUIERDA	*/
#define VELOCIDAD_IZQUIERDA_YMPI	VELOCIDAD_DERECHA_YMPD
#define VELOCIDAD_DERECHA_YMPI		VELOCIDAD_IZQUIERDA_YMPD

/*	AFUERA POR IZQUIERDA	*/
#define VELOCIDAD_IZQUIERDA_API		VELOCIDAD_DERECHA_APD
#define VELOCIDAD_DERECHA_API		VELOCIDAD_IZQUIERDA_APD

/*	VOLVIENDO POR IZQUIERDA	*/
#define VELOCIDAD_IZQUIERDA_VEPI	VELOCIDAD_DERECHA_VEPD
#define VELOCIDAD_DERECHA_VEPI		VELOCIDAD_IZQUIERDA_VEPD

/*	VOLVIO POR IZQUIERDA	*/
//#define VELOCIDAD_IZQUIERDA_VOPI	VELOCIDAD_DERECHA_VOPD
//#define VELOCIDAD_DERECHA_VOPI		VELOCIDAD_IZQUIERDA_VOPD



#endif
