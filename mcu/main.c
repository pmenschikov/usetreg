#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD	19200L
#define UBRR	(F_CPU/16/BAUD-1)

static void init()
{
	UBRRH = (unsigned char)(UBRR>>8);
	UBRRL = (unsigned char)(UBRR&0xFF);

	UCSRB = _BV(RXEN) | _BV(TXEN);

//	UCSRB |= _BV(RXCIE);

	UCSRC=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(0<<UCSZ2)|(1<<UCSZ1)|(1<<UCSZ0);
	
}

#if 0
ISR(USART_RXC_vect)
{
	uint8_t b;
	b = UDR;
	if( rx_buf_pos < RX_BUFFER_SIZE )
	{
		rx_buffer[rx_buf_pos] = b;
		++rx_buf_pos;
	}
}
#endif

void usart_sendchar( unsigned char data )
{
	while ( !(UCSRA & (1<<UDRE)) ); //Ожидание опустошения буфера приема
	UDR = data; //Начало передачи данных
}

char usart_getchar()
{
	while( !(UCSRA & _BV(RXC)) );
	return UDR;
}

union data_union_t
{
	uint8_t d8;
	uint16_t d16;
	uint8_t bytes[2];
};

int __attribute((OS_main)) main()
{
	uint8_t d,i;
	union data_union_t data;

	char what;
	char addr;

	init();

	while(1)
	{
		// first byte is what todo
		what = usart_getchar();
		// second byte address of register
		addr = usart_getchar();
		switch(what)
		{
			case 0:
				// write 8 bit register
				// third - data
				data.d8 = usart_getchar();
				*(volatile uint8_t *)(addr) = data.d8;
				break;

			case 1:
				// write 16 bit register
				data.bytes[0] = usart_getchar();
				data.bytes[1] = usart_getchar();
				*(volatile uint16_t *)(addr) = data.d16;
				break;
			case 2:
				// read 8 bit register
				data.d8 = *(volatile uint8_t*)(addr);
				usart_sendchar(data.d8);
				break;
			case 3:
				// read 16 bit register
				data.d16 = *(volatile uint16_t *)(addr);
				usart_sendchar(data.bytes[0]);
				usart_sendchar(data.bytes[1]);
				break;
		}
	}

	return 0;
}

