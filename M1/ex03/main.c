#include <avr/io.h>
#include <util/delay.h>

void        init()
{
    DDRB |= (1 << DDB1);    
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    DDRD &= ~(1 << DDD2); //sw1
    PORTD |= (1 << PD2);

    DDRD &= ~(1 << DDD4); //sw2
    PORTD |= (1 << PD4); 
    ICR1 = 62499;
}

int main()
{
    int n = 1;
    uint8_t last_sw1 = 1;    //button last state
    uint8_t last_sw2 = 1;

    init();
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12);

    while (1)
    {
        uint8_t sw1 = (PIND >> PD2) & 1;
        uint8_t sw2 = (PIND >> PD4) & 1;
        if (last_sw1 == 1 && sw1 == 0 && n < 10)
            n++;
        if (last_sw2 == 1 && sw2 == 0 && n > 1)
            n--;

        last_sw1 = sw1;
        last_sw2 = sw2;

        OCR1A = ((16000000/256) * n * 0.1) - 1;;
        _delay_ms(20);
    }
    return (0);
}