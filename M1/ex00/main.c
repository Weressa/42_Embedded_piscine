#include <avr/io.h>

int main()
{
    DDRB |= (1 << DDB1);

    while (1)   
    {
        volatile uint32_t i = 1;
        while(i < 250000UL)
            i++;
        PORTB ^= (1 << PB1);
    }
}