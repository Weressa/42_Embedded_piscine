#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int n = 0;

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

void INT0_vect(void) __attribute__((signal));

void INT0_vect(void)
{
    if (n < 15)
        n++;
    light(n);
    _delay_ms(50);
    EIFR = (1 << INTF0);
}

void PCINT2_vect(void) __attribute__((signal));

void PCINT2_vect(void)
{
    if (n > 0)
        n--;
    light(n);
    _delay_ms(50);
    //PCIFR: Pin Change Interrupt Flag Register
    //PCIF2: Pin Change Interrupt Flag 2
    PCIFR |= (1 << PCIF2);
}

int main()
{
    initialize_leds();
    initialize_buttons();

    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0);

    //PCICR: Pin Change Interrupt Control Register
    //PCIE2: Pin Change Interrupt Enable 2 )(pcint 16-23)
    PCICR |= (1 << PCIE2);

    //PCMSK2: Pin Change Mask Register 2
    //PCINT20: pin change interrupt is enabled on TD4
    PCMSK2 |= (1 << PCINT20);

    SREG |= (1 << 7);

    while (1)
    {}
    return (0);
}