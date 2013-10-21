#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"


/* =================================================== */
/* Buffers de transmision y recepcion                  */
/* =================================================== */
volatile unsigned char tx_buff[TX_BUFF_SIZE];
volatile unsigned char rx_buff[RX_BUFF_SIZE];
/* =================================================== */

/* =================================================== */
/* Indices de los buffers                              */
/* =================================================== */
volatile unsigned char tx_in;
volatile unsigned char tx_out;		

volatile unsigned char rx_in;
volatile unsigned char rx_out;
/* =================================================== */

// Variables del sistema
extern volatile global_stat_t global_status;   // Indica si el sistema está online u offline respecto del server.
extern volatile unsigned char new_status;      // Guarda el comando que recibe del server, para modificar los parámetros del sistema
extern volatile unsigned char update_device;   // Indica que llego un dato nuevo desde el server, relacionado con la configuración
extern volatile unsigned char new_config;      // Guarda el comando que recibe del server, para modificar los parámetros del equipo
extern volatile unsigned char update_status;   // Indica si se debe actualizar el sistema o no, debido a la llegada de un nuevo comando

volatile unsigned char pos_data_uart;    // Guarda la posicion del primer dato del payload   
volatile unsigned char data_count_uart;  // Cuenta la cantidad de datos recibidos como parte del payload
volatile unsigned char flag_sinc_uart;   // Cuando vale 1 indica que recibí el byte de sincronizacion y lo siguiente es el payload
volatile unsigned char set_new_date;     // Indica que el server va a actualizar la fecha, y el proximo payload es la nueva fecha
volatile unsigned char new_date_counter; // Cuenta la cantidad de bytes recibidos para saber cuando se completa el payload

volatile static_queue_s buffer_tx_rs232;
volatile static_queue_s buffer_rx_rs232;


void USART0Setup(uint16_t baudrate, uint8_t char_size, uint8_t stop_bit, uint8_t parity, uint8_t mode){

    set_new_date = false;
    new_date_counter = 0;
    init_queue(&buffer_rx_rs232, DATE_STRING_LENGTH);

	UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // activamos la recepcion y transmision en el USART0

	UBRR0H = (BAUD_PRESCALER(baudrate)>>8); // seteamos los prescalers del baudrate
	UBRR0L = (BAUD_PRESCALER(baudrate));
	
	UCSR0C |= (mode<<UMSEL00); // seteamos el modo de operacion syncronico o asyncronico

	UCSR0C |= (parity<<UPM00); // seteamos la cantidad de bits de paridad que vamos a usar

	UCSR0C |= (stop_bit<<USBS0); // seteamos la cantidad de bits de parada que vamos a usar

	UCSR0C |= (char_size<<UCSZ00);

#ifdef USART0_INTERRUPT
    UCSR0B |= (1<<RXCIE0) | (1<<UDRIE0);
    sei();
#endif
}


unsigned char USART0Receive(void){
#ifdef USART0_INTERRUPT
    unsigned char c;
    while(USART0RXBuffLen() == 0);
    c = rx_buff[rx_out & RX_MASK];
    rx_out++; 
    return (c); // si hay info retorno el dato
#else
	while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
#endif
}

void USART0Transmit(char c){
#ifdef USART0_INTERRUPT
    while((TX_BUFF_SIZE - USART0TXBuffLen()) <= 2); // si el buffer esta lleno espero a que la interrupcion libere espacio
    tx_buff[tx_in & TX_MASK] = c;
    tx_in++;
    UCSR0B |= (1<<UDRIE0); //habilito la interrupcion
#else
	while (!(UCSR0A & (1<<UDRE0))); 
	UDR0 = c;
#endif
}

void USART0Puts(char *string){
	while (*string)
		USART0Transmit(*string++);
}

void USART0PutsP(char *string){
    char b;

    while ((b = pgm_read_byte(string++)) != 0)
        USART0Transmit(b);
}

#ifdef USART0_INTERRUPT
unsigned char USART0TXBuffLen(void){
    return(tx_in - tx_out);
}

unsigned char USART0RXBuffLen(void){
    return(rx_in - rx_out);
}

void uart_flush(void)
{
    rx_in = rx_out;
}

#endif
