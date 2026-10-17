#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void    init_led()
{
    DDRD |= (1 << DDD5);//red
    DDRD |= (1 << DDD6); //green
    DDRD |= (1 << DDD3); //blue
    PORTD &= ~(1 << PD5);
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD3);

}

void init_rgb()
{
    // Timer 0 Controls PD6 and PD5
    // - COM0A1 / COM0B1: Clear OC0A/OC0B on Compare Match (Non-inverting PWM)
    // - WGM01 / WGM00: Set Fast PWM mode
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    
    // - CS01 / CS00: Set Prescaler to 64
    TCCR0B = (1 << CS01) | (1 << CS00);

    // Timer 2 Controls PD3
    // COM2B1: puts OC2B on Compare Match (Non-inverting PWM)
    // WGM21 / WGM20: Set Fast PWM mode
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    
    // CS22: Set Prescaler to 64
    TCCR2B = (1 << CS22);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
        // PD5 is tied to OCR0B
        OCR0B = r; 
        // PD6 is tied to OCR0A
        OCR0A = g; 
        // PD3 is tied to OCR2B
        OCR2B = b;
}

void wheel(uint8_t pos) 
{
        pos = 255 - pos;
        if (pos < 85)
        {
                set_rgb(255 - pos * 3, 0, pos * 3);
        } 
        else if (pos < 170) 
        {
                pos = pos - 85;
                set_rgb(0, pos * 3, 255 - pos * 3);
        } 
        else
        {
                pos = pos - 170;
                set_rgb(pos * 3, 255 - pos * 3, 0);
        }
}

int main()
{
    init_led();
    init_rgb();
    uint8_t i = 0;
    while(1)
    {
        wheel(i);
        //i reset to 0 ounce overflow
        i++;
        _delay_ms(25);
    }    
    return (0);
}
