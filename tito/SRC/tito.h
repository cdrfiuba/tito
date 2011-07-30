#ifndef HEADER_TITO
#define HEADER_TITO

void MoverIzquierda (void);
void MoverDerecha (void);
void MoverAdelante (void);
void startup (void);

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


#define PORT_ENABLE_A_NAME  	B
#define ENABLE_A_NUMBER     	1
#define PORT_ENABLE_A    def_port_reg(PORT_ENABLE_A_NAME)
#define PIN_ENABLE_A      def_pin_reg(PORT_ENABLE_A_NAME)
#define DDR_ENABLE_A      def_ddr_reg(PORT_ENABLE_A_NAME)

#define PORT_ENABLE_B_NAME  	B
#define ENABLE_B_NUMBER     	2
#define PORT_ENABLE_B    def_port_reg(PORT_ENABLE_B_NAME)
#define PIN_ENABLE_B      def_pin_reg(PORT_ENABLE_B_NAME)
#define DDR_ENABLE_B      def_ddr_reg(PORT_ENABLE_B_NAME)


#define PORT_IN_1_A_NAME	D
#define IN_1_A_NUMBER		1
#define PORT_IN_1_A    		def_port_reg(PORT_IN_1_A_NAME)
#define PIN_IN_1_A			def_pin_reg(PORT_IN_1_A_NAME)
#define DDR_IN_1_A			def_ddr_reg(PORT_IN_1_A_NAME)

#define PORT_IN_2_A_NAME	D
#define IN_2_A_NUMBER		0
#define PORT_IN_2_A    		def_port_reg(PORT_IN_2_A_NAME)
#define PIN_IN_2_A			def_pin_reg(PORT_IN_2_A_NAME)
#define DDR_IN_2_A			def_ddr_reg(PORT_IN_2_A_NAME)

#define PORT_IN_3_B_NAME	C
#define IN_3_B_NUMBER		4
#define PORT_IN_3_B    		def_port_reg(PORT_IN_3_B_NAME)
#define PIN_IN_3_B			def_pin_reg(PORT_IN_3_B_NAME)
#define DDR_IN_3_B			def_ddr_reg(PORT_IN_3_B_NAME)

#define PORT_IN_4_B_NAME	C
#define IN_4_B_NUMBER		5
#define PORT_IN_4_B    		def_port_reg(PORT_IN_4_B_NAME)
#define PIN_IN_4_B			def_pin_reg(PORT_IN_4_B_NAME)
#define DDR_IN_4_B			def_ddr_reg(PORT_IN_4_B_NAME)


#define SetBit(Byte,Bit)	 (Byte |= (1<<Bit))
#define	ClearBit(Byte,Bit)	 (Byte &= (~(1<<Bit)))
#define IsBitSet(Byte,Bit)	 ( (Byte & (1<<Bit)) ? 1 : 0 )

#define concat(a,b)		a ## b
#define def_port_reg(name)	concat(PORT,name)
#define def_pin_reg(name)	concat(PIN,name)
#define def_ddr_reg(name)	concat(DDR,name)

#endif
