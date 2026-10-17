#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void    init_led()
{
    DDRD |= (1 << DDD5);//red
    DDRD |= (1 << DDD6); //green
    DDRD |= (1 << DDD3); //blue
}

void    rgb()
{
        PORTD |= (1 << PD5);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
        PORTD |= (1 << PD6);
        _delay_ms(1000);
        PORTD &= ~(1 << PD6);
        PORTD |= (1 << PD3);
        _delay_ms(1000);
        PORTD &= ~(1 << PD3);
}

void    yellow()
{
        PORTD |= (1 << PD5);
        PORTD |= (1 << PD6);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
        PORTD &= ~(1 << PD6);
}

void    cyan()
{
        PORTD |= (1 << PD6);
        PORTD |= (1 << PD3);
        _delay_ms(1000);
        PORTD &= ~(1 << PD6);
        PORTD &= ~(1 << PD3);
}

void    magenta()
{
        PORTD |= (1 << PD5);
        PORTD |= (1 << PD3);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
        PORTD &= ~(1 << PD3);
}

void    white()
{
        PORTD |= (1 << PD5);
        PORTD |= (1 << PD6);
        PORTD |= (1 << PD3);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
        PORTD &= ~(1 << PD3);
        PORTD &= ~(1 << PD6);
}

int main()
{
    init_led();
    while(1)
    {
        rgb();
        yellow();
        cyan();
        magenta();
        white();
    }    
    return (0);
}
