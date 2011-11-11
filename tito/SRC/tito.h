#ifndef HEADER_TITO
#define HEADER_TITO
/**
 Prototipos
*/
void startup (void);
uint16_t obtener_evento(void);

/**
 estados y eventos para la fsm
*/
typedef enum estados {
	ST_CUALQUIERA,

	ST_EN_LINEA,

	ST_YENDOSE_POCO_POR_DERECHA,
	ST_YENDOSE_MUCHO_POR_DERECHA,
	ST_AFUERA_POR_DERECHA,
	ST_VOLVIENDO_POR_DERECHA,
	ST_VOLVIO_POR_DERECHA,

	ST_YENDOSE_POCO_POR_IZQUIERDA,
	ST_YENDOSE_MUCHO_POR_IZQUIERDA,
	ST_AFUERA_POR_IZQUIERDA,
	ST_VOLVIENDO_POR_IZQUIERDA,
	ST_VOLVIO_POR_IZQUIERDA,
	ST_ERROR
} estados_t;
typedef enum eventos {
	EV_CUALQUIERA = 8,

	EV_SENSORES_NNN = 0,
	EV_SENSORES_NNB = 1,
	EV_SENSORES_NBN = 2,
	EV_SENSORES_NBB = 3,
	EV_SENSORES_BNN = 4,
	EV_SENSORES_BNB = 5,
	EV_SENSORES_BBN = 6,
	EV_SENSORES_BBB = 7
} eventos_t;

#define PORT_LED_1_NAME  	C
#define LED_1_NUMBER     	3
#define PORT_LED_1    def_port_reg(PORT_LED_1_NAME)
#define PIN_LED_1      def_pin_reg(PORT_LED_1_NAME)
#define DDR_LED_1      def_ddr_reg(PORT_LED_1_NAME)

#define PORT_LED_2_NAME  	C
#define LED_2_NUMBER     	2
#define PORT_LED_2    def_port_reg(PORT_LED_2_NAME)
#define PIN_LED_2      def_pin_reg(PORT_LED_2_NAME)
#define DDR_LED_2      def_ddr_reg(PORT_LED_2_NAME)

#define PORT_LED_3_NAME  	C
#define LED_3_NUMBER     	1
#define PORT_LED_3    def_port_reg(PORT_LED_3_NAME)
#define PIN_LED_3      def_pin_reg(PORT_LED_3_NAME)
#define DDR_LED_3      def_ddr_reg(PORT_LED_3_NAME)

#define PORT_LED_4_NAME  	C
#define LED_4_NUMBER     	0
#define PORT_LED_4    def_port_reg(PORT_LED_4_NAME)
#define PIN_LED_4      def_pin_reg(PORT_LED_4_NAME)
#define DDR_LED_4      def_ddr_reg(PORT_LED_4_NAME)

#define PORT_SENSOR_1_NAME  	D
#define SENSOR_1_NUMBER     	5
#define PORT_SENSOR_1    def_port_reg(PORT_SENSOR_1_NAME)
#define PIN_SENSOR_1      def_pin_reg(PORT_SENSOR_1_NAME)
#define DDR_SENSOR_1      def_ddr_reg(PORT_SENSOR_1_NAME)

#define PORT_SENSOR_2_NAME  	D
#define SENSOR_2_NUMBER     	6
#define PORT_SENSOR_2    def_port_reg(PORT_SENSOR_2_NAME)
#define PIN_SENSOR_2      def_pin_reg(PORT_SENSOR_2_NAME)
#define DDR_SENSOR_2      def_ddr_reg(PORT_SENSOR_2_NAME)

#define PORT_SENSOR_3_NAME  	D
#define SENSOR_3_NUMBER     	7
#define PORT_SENSOR_3    def_port_reg(PORT_SENSOR_3_NAME)
#define PIN_SENSOR_3      def_pin_reg(PORT_SENSOR_3_NAME)
#define DDR_SENSOR_3      def_ddr_reg(PORT_SENSOR_3_NAME)

#define PORT_SENSOR_CURVA_NAME  	D
#define SENSOR_CURVA_NUMBER     	2
#define PORT_SENSOR_CURVA    def_port_reg(PORT_SENSOR_CURVA_NAME)
#define PIN_SENSOR_CURVA      def_pin_reg(PORT_SENSOR_CURVA_NAME)
#define DDR_SENSOR_CURVA      def_ddr_reg(PORT_SENSOR_CURVA_NAME)

#define PORT_BOTON_NAME  	B
#define BOTON_NUMBER     	0
#define PORT_BOTON       def_port_reg(PORT_BOTON_NAME)
#define PIN_BOTON         def_pin_reg(PORT_BOTON_NAME)
#define DDR_BOTON  	      def_ddr_reg(PORT_BOTON_NAME)

#define SetBit(Byte,Bit)	 (Byte |= (1<<Bit))
#define	ClearBit(Byte,Bit)	 (Byte &= (~(1<<Bit)))
#define IsBitSet(Byte,Bit)	 ((Byte>>Bit) & 1)

#define SENSOR_IZQUIERDA	IsBitSet(PIN_SENSOR_1, SENSOR_1_NUMBER)
#define SENSOR_CENTRO		IsBitSet(PIN_SENSOR_2, SENSOR_2_NUMBER)
#define SENSOR_DERECHA		IsBitSet(PIN_SENSOR_3, SENSOR_3_NUMBER)
#define SENSOR_CURVA		IsBitSet(PIN_SENSOR_CURVA, SENSOR_CURVA_NUMBER)

#define BOTON_APRETADO 		(!(PINB&(1<<PB0)))
#define BOTON_NO_APRETADO 	(PINB&(1<<PB0))

/*
#define concat(a,b)		a ## b
#define def_port_reg(name)	concat(PORT,name)
#define def_pin_reg(name)	concat(PIN,name)
#define def_ddr_reg(name)	concat(DDR,name)
*/
#endif
