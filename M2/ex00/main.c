#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//to test screen /dev/ttyUSB0 115200
//to terminate ct+a k y

# define UART_BAUDRATE 115200
# define F_CPU 16000000UL

void    uart_init()
{
    // 19.3.1 activate UBRR en mode double vitesse (U2X0 = 1)
    uint16_t ubrr = (F_CPU / (8 * UART_BAUDRATE )) - 1;
    
    UBRR0H = (uint8_t)(ubrr>>8);
    UBRR0L = (uint8_t)ubrr;
    
    //30. bit U2X0 (Double Transmission Speed) to 1
    UCSR0A |= (1 << U2X0);

    //19.3. Registre UCSR0B (USART Control and Status Register B)
    // bit TXEN0 (Transmitter Enable) to 1.    
    UCSR0B = (1<<TXEN0);

    //19.10.4  8N1 happens in UCSR0C 
    //set  frame format (Configure data format, 8data, 1stop bit)
    UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

void    uart_tx(char c)
{
    //while UDRE0 = 0 (sending character) wait
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    
    //UDRE0 = 1, UDR0 can send new c
    UDR0 = c;
}

int main()
{
    uart_init();

    while (1)
    {
        uart_tx('Z');
        // delay 1 Hz (1s)
        _delay_ms(1000);
    }
}

/* 115200 8N1 ??
- Baud rate — vitesse de transmission = 115200 bit/s (UART classique)
- 8 : bit chars
- N : no parity
- 1 : stop bit

to ensure UART artificial bits are added:
    - Start bit
    - Stop bit*/

/*Registers:
UBRR0    USART Baud Rate Register, Registre de fréquence d'horloge du baud rate
UBRR0H et UBRR0L	Réglent la vitesse de transmission

UCSR0A          	USART Control and Status Register A)
                    Contient notamment des indicateurs 
                    d'état et le bit de double vitesse U2X0

UCSR0B	            Registre d'état/contrôle B.
                    Active l'émetteur avec TXEN0

UCSR0C	            Registre de format de trame. On y règle 
                    la taille des mots (8 bits via UCSZ00 et UCSZ01).
                    Configure le format des données, notamment 8 bits
                     et 1 bit d'arrêt

UDR0	            Registre de données. Écrire un caractère dedans lance 
                    son envoi physique, utilisé pour transmettre ou recevoir un octet
UDRE0	            Indique que le registre de données peut recevoir un nouvel octet
*/
