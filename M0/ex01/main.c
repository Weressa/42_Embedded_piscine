#include <avr/io.h>

int main()
{
    /*DDRB: Data Direction Register B
    PB0: Pin 1 of Port B
    1 << PB0 : take the number 1 and slide it left by 1 position,"
    which gives 00000001. Only bit 0 is on.
    |= means "turn on the bits I list, and leave all the others alone.*/
    
    DDRB |= (1 << DDB0); //DDRB direction (here output = 1) 
    PORTB |= (1 << PB0); //PORTB value (here 5V = 1)

// |= if DDB is 1 or msak (here 1) is 1 DDRB becomes 1 
    return (0);
}