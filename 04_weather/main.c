#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

#include "print.h"
#include "dht11.h"

// Update LED indicators of "state" of the room
// Green: excellent
// Yellow: not great
// Red: terrible
void update_leds(uint8_t temp, uint8_t hum);

int main(void)
{

    DDRD |= (1 << PD4);
    DDRD |= (1 << PD7);
    DDRB |= (1 << PB0);

    print_init();

    uint8_t temp, hum;

    while (1)
    {
        if (dht_read(&temp, &hum) == DHT_OK)
        {
            printf("Temperature: %d C, Humidity: %d %%\n", temp, hum);
            update_leds(temp, hum);
        }
        else
        {
            printf("DHT read error\n");
        }

        _delay_ms(10000);
    }
}

const uint8_t TEMP_GREEN_LOW = 22;
const uint8_t TEMP_GREEN_HIGH = 27;
const uint8_t TEMP_YELLOW_LOW = 19;
const uint8_t TEMP_YELLOW_HIGH = 30;

const uint8_t HUM_GREEN_LOW = 30;
const uint8_t HUM_GREEN_HIGH = 60;
const uint8_t HUM_YELLOW_LOW = 25;
const uint8_t HUM_YELLOW_HIGH = 70;

void update_leds(uint8_t temp, uint8_t hum)
{
    int pts = 0;

    if (temp < TEMP_YELLOW_LOW || temp > TEMP_YELLOW_HIGH)
    {
        pts = 2;
        goto done;
    }

    if (hum < HUM_YELLOW_LOW || hum > HUM_YELLOW_HIGH)
    {
        pts = 2;
        goto done;
    }

    if (temp < TEMP_GREEN_LOW || temp > TEMP_GREEN_HIGH)
    {
        ++pts;
    }

    if (hum < HUM_GREEN_LOW || hum > HUM_GREEN_HIGH)
    {
        ++pts;
    }

done:
    switch (pts)
    {
    case 0:
        PORTD |= (1 << PD4);
        PORTD &= ~(1 << PD7);
        PORTB &= ~(1 << PB0);
        break;
    case 1:
        PORTD &= ~(1 << PD4);
        PORTD |= (1 << PD7);
        PORTB &= ~(1 << PB0);
        break;
    default:
        PORTD &= ~(1 << PD4);
        PORTD &= ~(1 << PD7);
        PORTB |= (1 << PB0);
        break;
    }
}
