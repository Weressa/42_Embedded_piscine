#include <avr/io.h>
#include <util/delay.h>

int main()
{
    //initialize button
    uint8_t last = 1; //to keep last state of button
    DDRD &= ~(1 << DDD2); //=0 input
    PORTD |= (1 << PD2);  //=1 pull-up
    //initialize led to off
    DDRB |= (1 << DDB0); // =1 output
    PORTB &= ~(1 << PB0); //=0 0v

    while (1)
    {
        uint8_t state = (PIND >> PD2) & 1; //catch button PD2 state
        if (last == 1 && state == 0) //button state compared to last
        {
            PORTB ^= (1 << PB0); //switch led state
            _delay_ms(20); //anti rebounce
        }
        last = state; //current state beecomes last state forn next time
    }
    return (0);
}