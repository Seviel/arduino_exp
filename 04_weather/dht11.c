#include <util/delay.h>
#include <avr/interrupt.h>

#include "dht11.h"

DHT11_STATUS dht_read(uint8_t *temp, uint8_t *humidity)
{
    uint8_t data[5] = {0};

    // Start signal
    DHT_OUTPUT();
    DHT_LOW();
    _delay_ms(20);

    DHT_HIGH();
    _delay_us(30);

    DHT_INPUT();

    // Disable interrupts
    cli();

    // Check for response
    if (DHT_READ())
    {
        // Error happened, enable interrupts and return
        sei();
        return DHT_ERROR;
    }

    _delay_us(80);

    if (!DHT_READ())
    {
        // Error happened, enable interrupts and return
        sei();
        return DHT_ERROR;
    }

    _delay_us(80);

    // Read 40 bits
    for (uint8_t i = 0; i < 40; i++)
    {
        // Wait for LOW signal
        while (!DHT_READ())
            ;

        _delay_us(40);

        // Read bit
        if (DHT_READ())
        {
            data[i / 8] |= (1 << (7 - (i % 8)));
        }

        // Wait for HIGH signal to end
        while (DHT_READ())
            ;
    }

    // Enable interrupts
    sei();

    // If checksum is bad, something went wrong
    if ((uint8_t)(data[0] + data[1] + data[2] + data[3]) != data[4])
    {
        return DHT_ERROR;
    }

    // 0th byte: humidity integer part
    // 1st byte: humidity decimal part
    // 2nd byte: temperature integer part
    // 3rd byte: temperature decimal part
    // 4th byte: checksum
    *humidity = data[0];
    *temp = data[2];

    return DHT_OK;
}
