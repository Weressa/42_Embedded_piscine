#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

# define UART_BAUDRATE 115200
# define F_CPU 16000000UL

void    uart_init()
{
    uint16_t ubrr = (F_CPU / (8 * UART_BAUDRATE )) - 1;
    UBRR0H = (uint8_t)(ubrr>>8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0A |= (1 << U2X0);
    //USART receiver pin enabled
    UCSR0B = (1<<TXEN0) | (1<<RXEN0);
    UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

char uart_rx(void)
{
    //wait till RXC0 becomes 1 (data received)
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return(UDR0);
}

void    uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
}

int main()
{
    uart_init();
    while (1)
    {
        char c = uart_rx();
        uart_tx(c);
    }
}
