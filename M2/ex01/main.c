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
    UCSR0B = (1<<TXEN0);
    UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

void    uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
}

void uart_printstr(const char* str)
{
    int i=0;
    while(str[i])
    {
        uart_tx(str[i]);
        i++;
    }
}

//make a function a signal handler
void u_print(void) __attribute__((signal));

void u_print(void)
{
    uart_printstr("Hello World!\r\n");
}

void    ft_timer()
{
    //prescaler 1024
    TCNT1 = 0;
    //(F_CPU * 2)/prescaler - 1 
    OCR1A = 31249;
    TCCR1A = 0;
    TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
    //Timer1 interupt flag
    TIMSK1 |= (1 << OCIE1A);
}

int main()
{
    uart_init();
    u_print();
    // delay 1 Hz (1s)
    ft_timer();
    //6.3.1 set bit I (Global Interrupt Enable which is bit 7) to 1 in the status register
    SREG |= (1 << 7);
    while (1)
    {
    }
}
