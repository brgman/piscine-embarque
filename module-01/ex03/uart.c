#include <avr/io.h>
#include <stdio.h>

#define F_CPU 16000000UL  // Fréquence du CPU
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void uart_init(void) {
    // Configure la vitesse
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)(UBRR_VALUE & 0xFF);

    // Active TX et RX
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Format : 8 bits, 1 stop bit, pas de parité
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send_char(char c) {
    while (!(UCSR0A & (1 << UDRE0))); // Attend que le buffer soit vide
    UDR0 = c;
}

void uart_send_string(const char *s) {
    while (*s) {
        uart_send_char(*s++);
    }
}

// Redirige printf vers UART
int uart_putchar(char c, FILE *stream) {
    if (c == '\n') uart_putchar('\r', stream); // retour chariot
    uart_send_char(c);
    return 0;
}

// Fichier de flux pour printf
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
