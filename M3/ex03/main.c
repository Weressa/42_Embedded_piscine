#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

# define UART_BAUDRATE 115200
# define F_CPU 16000000UL

void init_rgb()
{
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS01) | (1 << CS00);
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22);
}

void    init_led()
{
    DDRD |= (1 << DDD5);//red
    DDRD |= (1 << DDD6); //green
    DDRD |= (1 << DDD3); //blue
    OCR0B = 0; 
    OCR0A = 0; 
    OCR2B = 0;

}

void    uart_init()
{
    uint16_t ubrr = (F_CPU / (8 * UART_BAUDRATE )) - 1;
    UBRR0H = (uint8_t)(ubrr>>8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0A |= (1 << U2X0);
    UCSR0B = (1<<TXEN0) | (1<<RXEN0);
    UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

char uart_rx(void)
{
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

void uart_printstr(const char* str)
{
    int i=0;
    while(str[i])
    {
        uart_tx(str[i]);
        i++;
    }
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r; 
    OCR0A = g; 
    OCR2B = b;
}

int dec(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0') ;
    if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
    if (c >= 'A' && c <= 'F')
        return(c - 'A' + 10);
    return (0);
}

void extract_color(char *str) 
{
    uint8_t rgb[3];
    int i = 0;
    int j = 1;
    while (j <= 6)
    {
        rgb[i] = dec(str[j]) * 16 + dec(str[j+1]);
        i++;
        j+=2;
    }
    set_rgb(rgb[0], rgb[1], rgb[2]);
}

int is_hex(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
        return(1);
    return(0);
}

int main()
{
    char buffer[7];
    init_led();
    init_rgb();
    uart_init();
    while(1)
    {
        uart_printstr("Enter color (#RRGGBB): ");
        int i = 0;
        while (i < 7)
        {
            char c = uart_rx();
            uart_tx(c);
            if (i == 0 && c != '#')
            {
                uart_printstr("\r\nMust start with #\r\n");
                break;
            }
            if(i > 0 && !is_hex(c))
            {
                uart_printstr("\r\nWrong format (hexadecimal number only!)\r\n");
                break;
            }
            buffer[i] = c;
            i++;
        }
        if (i == 7)
        {
            uart_printstr("\r\n");
            extract_color(buffer);
        }
    }    
    return (0);
}
