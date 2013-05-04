/*
	Puertos:
			* 3 genericos
	Timers:
			* Timer0
	Interrupciones:
			* TIMER0_OVF_vect
*/

#ifndef __SENSORES_H__
#define __SENSORES_H__

/*******************************************************
* Constantes
*******************************************************/ 
// VERIFICAR PUERTO Y PIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define PORT_NAME_SENS1 C
#define PORT_NAME_SENS2 C
#define PORT_NAME_SENS3 C
#define PIN_NUM_SENS1 5
#define PIN_NUM_SENS2 4
#define PIN_NUM_SENS3 3

#define PORT_SENS1 def_port_reg(PORT_NAME_SENS1)
#define PIN_SENS1 def_pin_reg(PORT_NAME_SENS1)
#define DDR_SENS1 def_ddr_reg(PORT_NAME_SENS1)

#define PORT_SENS2 def_port_reg(PORT_NAME_SENS2)
#define PIN_SENS2 def_pin_reg(PORT_NAME_SENS2)
#define DDR_SENS2 def_ddr_reg(PORT_NAME_SENS2)

#define PORT_SENS3 def_port_reg(PORT_NAME_SENS3)
#define PIN_SENS3 def_pin_reg(PORT_NAME_SENS3)
#define DDR_SENS3 def_ddr_reg(PORT_NAME_SENS3)

// Mascaras de los sensores
#define S1 _BV( PIN_NUM_SENS1 )
#define S2 _BV( PIN_NUM_SENS2 )
#define S3 _BV( PIN_NUM_SENS3 ) 
#define S1_S2 (S1 | S2)
#define S1_S3 (S1 | S3)
#define S2_S3 (S2 | S3)
#define S1_S2_S3 (S1 | S2 | S3)

/*******************************************************
* Tipos
*******************************************************/ 
typedef enum {SENS_IZQ=S1, SENS_IZQ_CENT=S1_S2, SENS_CENT=S2, SENS_DER_CENT=S2_S3, SENS_DER=S3, SENS_IZQ_DER=S1_S3, TODOS=S1_S2_S3, NINGUNO=0} t_estado_sens;

/*******************************************************
* Variables globales
*******************************************************/ 
// Variable para guardar el valor de los sensores
// bit PIN_NUM_SENS1 --> Sensor1
// bit PIN_NUM_SENS2 --> Sensor2
// bit PIN_NUM_SENS3 --> Sensor3
volatile t_estado_sens estado_sensores;


/*******************************************************
* Prototipos
*******************************************************/ 
void sensores_config(void);
void sensores_leer(void);
inline void sensores_muestrear(void);
inline void sensores_detener(void);

/*******************************************************
* Macros
*******************************************************/ 
#define concat(a,b)	a ## b
#define def_port_reg(name)	concat(PORT, name) 
#define def_pin_reg(name)	concat(PIN, name) 
#define def_ddr_reg(name)	concat(DDR, name) 

#endif
