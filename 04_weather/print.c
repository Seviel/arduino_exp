#include <avr/io.h>
#include <stdio.h>

// Frequenzy = 16000000 hz
// Baud rate = 9600
#define UBRR_VALUE 103 // Calculated as (Frequenzy / (16 * BaudRate)) - 1

static void uart_init()
{
    // Set baud rate
    UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L = (unsigned char)UBRR_VALUE;

    // Enable UART transmitter
    UCSR0B = (1 << TXEN0);

    // 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static void uart_transmit(char data)
{
    // Wait until transmit buffer empty
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    // Put data into buffer
    UDR0 = data;
}

// This function is needed so we can connect stdout to uart
static int uart_putchar(char c, FILE *stream)
{
    (void)stream;

    if (c == '\n')
    {
        uart_transmit('\r');
    }

    uart_transmit(c);
    return 0;
}

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void print_init()
{
    uart_init();
    stdout = &uart_stdout;
}
