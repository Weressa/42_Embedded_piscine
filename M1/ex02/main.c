#include <avr/io.h>

    /* changement par rapport au dernier exo le mode CTC au PWM
    (Pulse Width Modulation).
    
    */
   int main()
   {
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1 = 0;
        DDRB |= (1 << DDB1);

    /* OCR1A est la duree active de la sortie (ancien example 0.5s)
    (16000000÷256)x 0.1 - 1 = 6 249
       ICR1 est la duree totale du cycle
    16000000÷256 - 1 = 62 499*/
    ICR1 = 62499;
    OCR1A = 6249;

    //pour la sortie PWM. Il faut donc inverser COM1A1 = 1 et COM1A0 = 0 et WGM11 = 1.
        TCCR1A = (1 << COM1A1) | (1 << WGM11);
    //Fast PWM Timer1 mode 14 TOP ICR1
        TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12);
    
    while (1)   
    {}
}