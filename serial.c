// SEE ATMEGA328p docs — chapter 19

#define BAUD 9600UL
#define F_CPU 16000000UL
#define BAUD_RATE_REGISTER F_CPU / (16UL * BAUD) - 1

#include <avr/io.h>

void UART_INIT() {
  UBRR0H = (BAUD_RATE_REGISTER >> 0x08);
  UBRR0L = BAUD_RATE_REGISTER;

  UCSR0B |= (0x01 << RXEN0) | (0x01 << TXEN0);
}

void UART_TRANSMIT(uint8_t data) {
  // hold for transmission completion
  while (!(UCSR0A & (0x01 << UDRE0)))
    ;
  UDR0 = data;
}

int main() {
  UART_INIT();
  uint8_t temp;

  DDRC = 0x00;
  DDRC |= 0x01 << DDC0;

  // Rx
  while (1) {
    // receive complete -> there are unread data in the receive buffer
    if ((UCSR0A >> RXC0) == 0x01) {
      // 1. read the value of UDR0
      temp = UDR0;

      // 2. write that value back to UDR0
      UART_TRANSMIT(temp);
    }
  }

  return 0;
}
