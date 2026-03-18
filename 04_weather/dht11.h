#ifndef DHT11_H
#define DHT11_H

#include "stdint.h"

#define DHT_DDR DDRD
#define DHT_PORT PORTD
#define DHT_PIN PIND
#define DHT_BIT PD2

// Set DHT data pin to input
#define DHT_INPUT() (DHT_DDR &= ~(1 << DHT_BIT))
// Set DHT data pin to output
#define DHT_OUTPUT() (DHT_DDR |= (1 << DHT_BIT))
// Set DHT data pin to low
#define DHT_LOW() (DHT_PORT &= ~(1 << DHT_BIT))
// Set DHT data pin to high
#define DHT_HIGH() (DHT_PORT |= (1 << DHT_BIT))
// Read DHT data pin
#define DHT_READ() (DHT_PIN & (1 << DHT_BIT))

typedef enum DHT11_STATUS
{
    DHT_ERROR = 0,
    DHT_OK
} DHT11_STATUS;

/// @brief Read temperature and humidity from DHT11 sensor
///
/// @param temp Output temperature
/// @param humidity Output humidity
DHT11_STATUS dht_read(uint8_t *temp, uint8_t *humidity);

#endif // DHT11_H
