#include <avr/io.h>
#include <util/delay.h>

void    initialize_leds()
{
    DDRB |= (1 << DDB0); // =1 output
    PORTB &= ~(1 << PB0); //=0 0v
    
    DDRB |= (1 << DDB1); // =1 output
    PORTB &= ~(1 << PB1); //=0 0v
    
    DDRB |= (1 << DDB2); // =1 output
    PORTB &= ~(1 << PB2); //=0 0v
    
    DDRB |= (1 << DDB4); // =1 output
    PORTB &= ~(1 << PB4); //=0 0v
}

void        initialize_buttons()
{
    DDRD &= ~(1 << DDD2); //sw1
    PORTD |= (1 << PD2);

    DDRD &= ~(1 << DDD4); //sw2
    PORTD |= (1 << PD4); 
}

void    light(int n)
{
    int leds = (n & 0x07) | ((n & 0x08) << 1); 
    // 0x07 equal 00000111
    // 0x08 equal 00001000 with << 1 becomes in correct position
    // result  = 00010111 like the leds

    PORTB = (PORTB & ~((1 << PB0)  //00000001 bit pos
                    | (1 << PB1)   //00000010
                    | (1 << PB2)   //00000100
                    | (1 << PB4))) //00010000 but ~ will inverse so we can get value
                    | leds; //with leds
}

int main()
{
    int n = 0;
    uint8_t last_sw1 = 1;    // last state
    uint8_t last_sw2 = 1;

    initialize_leds();
    initialize_buttons();
    while (1)
    {
        uint8_t sw1 = (PIND >> PD2) & 1;
        uint8_t sw2 = (PIND >> PD4) & 1;
        if (last_sw1 == 1 && sw1 == 0 && n < 15)
            n++;
        if (last_sw2 == 1 && sw2 == 0 && n > 0)
            n--;

        last_sw1 = sw1;
        last_sw2 = sw2;

        light(n);
        _delay_ms(20);
    }
    return (0);
}