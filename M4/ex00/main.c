#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void INT0_vect(void) __attribute__((signal));

void INT0_vect(void)
{
    PORTB ^= (1 << PB0);
    _delay_ms(10);
    //EIFR: External Interrupt Flag Register
    //INTF0: External Interrupt Flag 0 is cleared after routine executed
    EIFR = (1 << INTF0);
}


int main()
{
    DDRB |= (1 << DDB0); // led output
    DDRD &= ~(1 << DDD2); //button input
    PORTD |= (1 << PD2);  //pull-up enabled

    // EICRA: External Interrupt Control Register A
    //ISC01 and ISC00: Interrupt Sense Control 0 Bit 1 and 0 
    //interrupt triggered on rising edge (button pressed)
    EICRA |= (1 << ISC01) | (1 << ISC00);
    
    //External Interrupt Mask Register
    //enable INT0 as interrupt
    EIMSK |= (1 << INT0);

    //Global Interrupt Enabled (bit 7)
    SREG |= (1 << 7);
    while (1) 
    {}
    return (0);
}