#include <stdlib.h>
#include <limits.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t leds_on = 0;
volatile int led_switch_cnt = 0;

const int ARRAY_SIZE = 100;

int main(void)
{
    // Set output pins
    DDRD |= (1 << PD4);
    DDRD |= (1 << PD7);
    DDRB |= (1 << PB0);
    DDRB |= (1 << PB5);

    // Unset the builtin LED
    PORTB = PORTB & ~(1 << PB5);

    // Setup the timer
    TCCR1B |= (1 << WGM12);              // CTC mode
    OCR1A = 15624;                       // 1 Hz with 16MHz / 1024
    TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024
    TIMSK1 |= (1 << OCIE1A);             // enable compare interrupt

    // Enable interrupts
    sei();

    float *farray = malloc(sizeof(float) * ARRAY_SIZE);
    int *iarray = malloc(sizeof(int) * ARRAY_SIZE);

    float fres = 0.0;
    int ires = 0;

    while (1)
    {
        // Just some nonsense code to keep the processor doing something for no particular reason :D
        if (leds_on)
        {
            for (int i = 0; i < ARRAY_SIZE; ++i)
            {
                farray[i] = (float)i * (float)led_switch_cnt;
            }
            for (int i = 0; i < ARRAY_SIZE - 4; ++i)
            {
                fres += farray[i + 4] - farray[i + 3] + farray[i + 2] / farray[i + 1] * farray[i];
            }
        }
        else
        {
            for (int i = 0; i < ARRAY_SIZE; ++i)
            {
                iarray[i] = (float)i * (float)led_switch_cnt;
            }
            for (int i = 0; i < ARRAY_SIZE - 4; ++i)
            {
                ires += iarray[i + 4] - iarray[i + 3] + iarray[i + 2] / iarray[i + 1] * iarray[i];
            }
        }

        if (fres == 8.0 || ires == 8)
        {
            PORTB ^= (1 << PB0);
        }
    }
}

ISR(TIMER1_COMPA_vect)
{
    // Toggle the leds
    PORTD ^= (1 << PD4);
    PORTD ^= (1 << PD7);
    PORTB ^= (1 << PB0);

    leds_on = !leds_on;

    ++led_switch_cnt;

    if (led_switch_cnt == INT_MAX)
    {
        led_switch_cnt = 0;
    }
}
