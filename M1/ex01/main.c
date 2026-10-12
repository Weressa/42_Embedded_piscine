#include <avr/io.h>

    /* TCCR1A is control register for Timer1 , it has the bits
    COM1A1 and COM1A0 which control pin OC1A (which is PB1) when
    the timer reaches its target 
    
    TCCR1A
    Bit:   7       6       5       4       3  2     1      0
          COM1A1  COM1A0  COM1B1  COM1B0   -  -   WGM11  WGM10

    DDRB / PORTB are controlled by you: you write them and
    the CPU changes the pin However COM1A1/COM1A0 don't drive
    the pin themselves. They tell the timer how it is allowed
    to take control of the pin.


    When COM1A1:COM1A0 is not 00, the timer overrides the normal 
    PORTB behavior on PB1. That's why the code still needs 
    DDRB |= (1 << PB1): the pin must be an output, but the timer
    decides when it flips, not PORTB.*/
    //CTC = Clear Timer on Compare Match

    //reglage principal dans TCCR1A , reglae vitesse dans TCCR1B
    
    
    /*
    WGM12 sert à choisir le mode de fonctionnement du compteur
    => mode CTC WGM12 = 1
    CS12 participe au choix de la vitesse du compteur
    */
   int main()
   {
        DDRB |= (1 << DDB1);

    //TCNT1 initialise a 0 
        TCNT1 = 0;   
    
    /*le registre OCR1A indique la limite du compteur
    comme frequence 16MHz et prescaler plus proche 256 (1024 donne
    valeur approximative et inf 256 comptage trop grand) 
    compteur recoit 16000000÷256=62500 imp/s => x 0.5 = 31 250 (compte de 0)*/
        OCR1A = 31249;

    //inverser la sortie à chaque comparaison. Il faut donc COM1A1 = 0 et COM1A0 = 1.
        TCCR1A |= (1 << COM1A0);
    
    /* Pour registre TCCR1B , CTC mode and prescaler :
    Mode WGM13 WGM12  WGM11 WGM10 Timer/Counter  TOP
    4     0    1      0      0      CTC         OCR1A 
    and CS12 = 1 for prescaler 256 so we configurate register :*/
    
        TCCR1B = (1 << WGM12) | (1 << CS12);
    
    while (1)   
    {}
}