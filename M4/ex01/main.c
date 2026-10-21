#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* led from 0 to 100% then from 100 to 0
in 8 bits from 0 to 255 then 255 to 0
=> 510 steps /second

F_CPU /510 = 31 3725 tic
timer0 max is 255 so with a prescaler 256
31 3725 /256 = 122.54
*/

void TIMER0_COMPA_vect(void) __attribute__((signal));

void TIMER0_COMPA_vect(void)
{
    //static to keep previous values
    static uint8_t steps = 0;
    static uint8_t direction = 1;

    steps += direction;
    if (steps == 255)
        direction = -1;
    else if (steps == 0)
        direction = 1;

    OCR1A = steps;
}

int main()
{
    DDRB |= (1 << DDB1); // led output
    
    //Timer1 in fast PWM mode
    TCCR1A = (1 << COM1A1) | (1 << WGM10);
    //fixe prescaler Timer1 a 64
    TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS11);
    OCR1A = 0;
    
    //Timer0 CTC mode (clear time on compare Match)
    TCCR0A = (1 << WGM01); //activate CTC mode 2
    TCCR0B = (1 << CS02); //activate prescaler to 256
    
    //counts to 122 activate interrupt and reset to 0
    OCR0A = 122;
    TIMSK0 |= (1 << OCIE0A);

    SREG |= (1 << 7);
    while (1) 
    {}
    return (0);
}