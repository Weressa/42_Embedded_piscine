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
    //RXCIE0 interupt pin activated after each reception
    UCSR0B = (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0);
    UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

void    uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
}

void u_print(void) __attribute__((signal));

void u_print(void)
{
    char c = UDR0;
    if (c > 64 && c < 91)
        uart_tx(c + 32);
    else if (c > 96 && c < 122)
        uart_tx(c - 32);
    else 
        uart_tx(c);
}

int main()
{
    uart_init();
    u_print();
    SREG |= (1 << 7);
    while (1)
    {}
}
