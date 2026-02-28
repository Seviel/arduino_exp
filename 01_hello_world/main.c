#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    // Set PORTB5 as an output
    DDRB = DDRB | (1 << DDB5);

    while (1)
    {
        // Set PORTB5
        PORTB = PORTB | (1 << PORTB5);

        _delay_ms(5000);
        // Unset PORTB5
        PORTB = PORTB & ~(1 << PORTB5);
        _delay_ms(100);
    }
}
