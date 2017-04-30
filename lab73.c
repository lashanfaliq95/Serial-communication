#include <avr/io.h>      
#define BAUDRATE 103  
void usart_init();
void usart_send(char data);
char usart_receive ();

int main(){

	usart_init();
	char data_rec[256] ;
	char data_snd[256] ="E/13/095-M.L Faliq\nE/13/056-A.H.S.J De Silva \nE/13/132- H.L.S Hashantha";
	
	while(1) {
		
		//char ch='A' ;
		char chR;
		int i = 0 ;
		int count ;
		
		
		//transmit
		for(i = 0;i < sizeof(data_snd) ; i++){
				usart_send(data_snd[i]);
		}
		
		// receive characters until \n
		while ((chR = usart_receive())!= '\r'){
			data_rec[i] = chR ;
			i++ ;
			
		}
		count = i;
		
		
		
	}

}


void usart_init()
{
	/*Set baud rate */
    //UBRR0H = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRR0L = BAUDRATE;                           // set baud rate
    UCSR0B|= (1<<TXEN0)|(1<<RXEN0);                // enable receiver and transmitter
    UCSR0C|= (3<<UCSZ00)|(0<<USBS0);   // 8bit data format,one stop bit
}


// function to send data
void usart_send(char data)
{
    while (!( UCSR0A & (1<<UDRE0)));                // wait while register is free
    UDR0 = data;                                   // load data in the register
}


// function to receive data
char usart_receive ()
{
    while(!(UCSR0A) & (1<<RXC0));                   // wait while data is being received
    return UDR0;                                   // return 8-bit data
}
