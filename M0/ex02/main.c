#include <avr/io.h>

int main()
{
    DDRB |= (1 << DDB0); //initialize direction to output

    //a button needs to be initialized to opposite
    DDRD &= ~(1 << DDD2); //inverse direction state to make it 0 (input)
    PORTD |= (1 << PD2);  //pull-up activated to 1 

    while (1)   //loop to keep it active
    {
        if (!(PIND & (1 << PD2)))
            PORTB |= (1 << PB0);
        else
            PORTB &= ~(1 << PB0);
        }
    return (0);
}