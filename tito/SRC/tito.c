#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "tito.h"
#include "lib/lib_pwm.h"
#include <avr/pgmspace.h>

void (*funciones[ST_MAX_ESTADOS])();

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
    ClearBit (DDR_SENSOR_CURVA, SENSOR_CURVA_NUMBER);

    // botón
    ClearBit (DDR_BOTON, BOTON_NUMBER);
    SetBit (PORT_BOTON, BOTON_NUMBER);


    // PWM
    pwm_config();
    pwm_start();

    // pone el flag global para activar interrupciones
    sei();

    // establezco la dirección de los motores
     
     

}

/*Tabla de Posibles transiciones*/
static const int transiciones[ST_MAX_ESTADOS][EV_MAX_SENSORES] PROGMEM = {
                              /*NNNN NNNB NNBN NNBB NBNN NBNB NBBN NBBB BNNN BNNB BNBN BNBB BBNN BBNB BBBN BBBB*/
/* En Linea*/                   { ME,YMPI,YPPI,YMPI,YPPD,  ME,  ME,  ME,YMPD,  ME,  ME,  ME,YMPD,  ME,  ME,  ME}, 

/* Yendose Poco por Derecha*/   {APD,  ME,  EL,  ME,  ME,  ME,  EL,  ME,YMPD,  ME,  ME,  ME,YMPD,  ME,  ME,  ME}, 
/* Yendose Mucho por Derecha*/  {APD,VOPD,VOPD,VOPD,  EL,  ME,VOPD,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME},
/* Afuera por Derecha*/         { ME,  ME,  ME,  ME,VEPD,  ME,  ME,  ME,VEPD,  ME,  ME,  ME,VEPD,  ME,  ME,  ME}, 
/* Volviendo por Derecha*/      {APD,  ME,VOPD,  ME,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volvio por Derecha*/         { ME,  ME,  EL,  ME,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,YPPD,  ME,  ME,  ME}, 

/* Yendose Poco por Izquierda*/ {API,YMPI,  ME,YMPI,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME},
/* Yendose Mucho por Izquierda*/{API,  ME,  EL,  ME,VOPI,  ME,VOPI,  ME,VOPI,  ME,  ME,  ME,VOPI,  ME,  ME,  ME}, 
/* Afuera por Izquierda*/       { ME,VEPI,VEPI,VEPI,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volviendo por Izquierda*/    {API,  ME,  EL,  ME,VOPI,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}, 
/* Volvio por Izquierda*/       { ME,  ME,  EL,YPPI,  EL,  ME,  EL,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME,  ME}  
};


void st_en_linea () {
    mot1_vel(255+COEFICIENTE_DERECHA*244);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*244);
     
     
};

void st_yendose_poco_por_derecha () {

    mot1_vel(255+COEFICIENTE_DERECHA*244);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*255);
     
     
    _delay_ms (5);  
//    mot1_vel(COEFICIENTE_IZQUIERDA * 100);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*179);
//     
     
};
void st_yendose_mucho_por_derecha () {
    mot1_vel(255-COEFICIENTE_DERECHA*255);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*244);
    
     
    _delay_ms (10);

    mot1_vel(255-COEFICIENTE_DERECHA*230);
//    mot2_vel(COEFICIENTE_ESTADO_PROBLEMATICO * COEFICIENTE_DERECHA *   100);
     
//     
};
void st_afuera_por_derecha () {
    mot1_vel(255-COEFICIENTE_DERECHA*255);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*244);
     
     
    _delay_ms (50);

    mot1_vel(255+COEFICIENTE_DERECHA*166);
//    mot2_vel(COEFICIENTE_DERECHA  *  100);
     
//     

};
void st_volviendo_por_derecha () {
    mot1_vel(255+COEFICIENTE_DERECHA*244);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*244);
     
     
    _delay_ms (10);
    
    mot1_vel(255+COEFICIENTE_DERECHA*102);
//    mot2_vel(COEFICIENTE_DERECHA   * 100);
     
//     
};
void st_volvio_por_derecha () {
    mot1_vel(255+COEFICIENTE_DERECHA*244);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*128);
     
     
    _delay_ms (10);
    
//    mot1_vel(COEFICIENTE_IZQUIERDA * 100);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*204);
//     
     
};

void st_yendose_poco_por_izquierda () {
    mot1_vel(255-COEFICIENTE_DERECHA*255);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*244);
     
     
    _delay_ms (5);
    
    mot1_vel(255+COEFICIENTE_DERECHA*179);
//    mot2_vel(COEFICIENTE_DERECHA   * 100);
     
//     
};
void st_yendose_mucho_por_izquierda () {
    mot1_vel(255+COEFICIENTE_DERECHA*144);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*255);
     
     
    _delay_ms (10);    
    
//    mot1_vel(COEFICIENTE_ESTADO_PROBLEMATICO * COEFICIENTE_IZQUIERDA * 100);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*230);
//     
     
};
void st_afuera_por_izquierda () {
    mot1_vel(255+COEFICIENTE_DERECHA*244);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*255);
     
     
    _delay_ms (50);    
    
//    mot1_vel(COEFICIENTE_ESTADO_PROBLEMATICO * COEFICIENTE_IZQUIERDA *  100);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*90);
//     
     
};
void st_volviendo_por_izquierda () {
    mot1_vel(255+COEFICIENTE_DERECHA*244);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*255);
     
     
    _delay_ms (10);    
    
//    mot1_vel(COEFICIENTE_IZQUIERDA * 100);
    mot2_vel(255+COEFICIENTE_IZQUIERDA*102);
//     
     
};
void st_volvio_por_izquierda () {
    mot1_vel(255+COEFICIENTE_DERECHA*244);
    mot2_vel(255-COEFICIENTE_IZQUIERDA*255);
     
     
    _delay_ms (10);    

    mot1_vel(255+COEFICIENTE_DERECHA*104);
//    mot2_vel(COEFICIENTE_DERECHA   * 100);
     
//     
};

/**
 función principal
*/
int main() {
    int estado_actual;
    int nuevo_estado;
    int estado_sensores;
    int i;
    
    startup();
    
    funciones[ST_EN_LINEA] = st_en_linea;
    
    funciones[ST_YENDOSE_POCO_POR_DERECHA] = st_yendose_poco_por_derecha;
    funciones[ST_YENDOSE_MUCHO_POR_DERECHA] = st_yendose_mucho_por_derecha;
    funciones[ST_AFUERA_POR_DERECHA] = st_afuera_por_derecha;
    funciones[ST_VOLVIENDO_POR_DERECHA] = st_volviendo_por_derecha;
    funciones[ST_VOLVIO_POR_DERECHA] = st_volvio_por_derecha;

    funciones[ST_YENDOSE_POCO_POR_IZQUIERDA] = st_yendose_poco_por_izquierda;
    funciones[ST_YENDOSE_MUCHO_POR_IZQUIERDA] = st_yendose_mucho_por_izquierda;
    funciones[ST_AFUERA_POR_IZQUIERDA] = st_afuera_por_izquierda;
    funciones[ST_VOLVIENDO_POR_IZQUIERDA] = st_volviendo_por_izquierda;
    funciones[ST_VOLVIO_POR_IZQUIERDA] = st_volvio_por_izquierda;
    
   
    while (1){
        for (i=0 ; i<ST_MAX_ESTADOS ; i++){
            (*funciones[i])();
            _delay_ms(1000);   
        }
    }

    
    
    while (1){

        // ciclos para esperar a que arranque cuando
        // se suelta el botón
        while (BOTON_NO_APRETADO);
        _delay_ms(50); //rebote botón
        

        while (BOTON_APRETADO);
        _delay_ms(5); //rebote botón

        // aceleración inicial gradual
        mot1_vel(300);
        mot2_vel(300);
        _delay_ms(50);
        
        // inicialización estado
        estado_actual = ST_EN_LINEA;
        (*funciones[estado_actual])();
        
        while (BOTON_NO_APRETADO) {
            estado_sensores = ESTADO_SENSORES; // obtiene el evento a procesar
            if ((nuevo_estado = pgm_read_byte_near(&(transiciones[estado_actual][estado_sensores]))) != ST_MAX_ESTADOS) {
                estado_actual = nuevo_estado;
                (*funciones[estado_actual])();
            }
        }

        // fin de tareas, para poder empezar de nuevo
        mot1_vel(255);
        mot2_vel(255);
        _delay_ms(50); //rebote botón

        while (BOTON_APRETADO);
        _delay_ms(50); //rebote botón
        
    }
}


/*void prueba_frenado(void){
    while(1)
    {   
        estado_sensores = ESTADO_SENSORES;
        if(estado_sensores)
        {   mot1_vel(COEFICIENTE_IZQUIERDA * 0);
            mot2_vel(COEFICIENTE_DERECHA   * 0);
             
             
        }
        else
        {   mot1_vel(COEFICIENTE_IZQUIERDA * 100);
            mot2_vel(COEFICIENTE_DERECHA   * 100);
             
             
        } 
    }
}*/

