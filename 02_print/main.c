#include <avr/io.h>
#include <util/delay.h>

// Frequenzy = 16000000 hz
// Baud rate = 9600
#define UBRR_VALUE 103 // Calculated as (Frequenzy / (16 * BaudRate)) - 1

void uart_init()
{
    // Set baud rate
    UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L = (unsigned char)UBRR_VALUE;

    // Enable UART transmitter
    UCSR0B = (1 << TXEN0);

    // 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(char data)
{
    // Wait until transmit buffer empty
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    // Put data into buffer
    UDR0 = data;
}

void uart_print(const char *str)
{
    while (*str)
    {
        uart_transmit(*str++);
    }
}

int main(void)
{
    uart_init();

    while (1)
    {
        uart_print("Hello from bare metal world!\r\n");
        _delay_ms(100000);
    }
}
