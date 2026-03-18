#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

#include "print.h"
#include "dht11.h"

int main(void)
{
    print_init();

    uint8_t temp, hum;

    while (1)
    {
        if (dht_read(&temp, &hum) == DHT_OK)
        {
            printf("Temperature: %d C, Humidity: %d %%\n", temp, hum);
        }
        else
        {
            printf("DHT read error\n");
        }

        _delay_ms(60000);
    }
}
