#define F_CPU 16000000UL
#define DEBOUNCE_MS 5

#include <avr/io.h>
#include <util/delay.h>

int button_is_pressed() {
  if ((PINC & (1 << PORTC0)) == 0) {
    _delay_ms(DEBOUNCE_MS);

    if ((PINC & (1 << PORTC0)) == 0) {
      return (1);
    }
  }

  return (0);
}

int main() {
  uint8_t LED_STATE = 0;
  uint8_t NEXT_LED_STATE = 1;

  // ----------- CONFIG -----------
  DDRC &= ~(1 << DDC0);
  PORTC |= (1 << PORTC0);

  // ----------- DEBUGGING -----------
  DDRD |= (1 << DDD0);
  PORTD = (PORTD & ~(1 << PORTD0)) | (LED_STATE << PORTD0);

  // ----------- EVENT LOOP -----------
  while (1) {
    if (button_is_pressed()) {
      if (LED_STATE != NEXT_LED_STATE) {
        LED_STATE = NEXT_LED_STATE;
        PORTD = (PORTD & ~(1 << PORTD0)) | (LED_STATE << PORTD0);
      }
    } else {
      if (LED_STATE == NEXT_LED_STATE) {
        NEXT_LED_STATE = (NEXT_LED_STATE == 0) ? 1 : 0;
      }
    }
  }

  return 0;
}
