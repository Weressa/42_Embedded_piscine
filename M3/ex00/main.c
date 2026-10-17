#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void    init_led()
{
    DDRD |= (1 << DDD5);//red
    DDRD |= (1 << DDD6); //green
    DDRD |= (1 << DDD3); //blue
}

int main()
{
    init_led();
    while(1)
    {
        PORTD = (1 << PD5);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
        PORTD = (1 << PD6);
        _delay_ms(1000);
        PORTD &= ~(1 << PD6);
        PORTD = (1 << PD3);
        _delay_ms(1000);
        PORTD &= ~(1 << PD3);
    }
    return (0);
}
