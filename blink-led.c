#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void setBits(uint8_t value) {
    PORTD = value;
    _delay_ms(25);
}


int main() {
    DDRD = 0xff;
    int i = -1;

    while (1) {
        i += 1;

        for (; i <= 7; ++i) {
            setBits(1 << i);
        }

        i -= 1;

        for (; i >= 0; --i) {
            setBits(1 << i);
        }

    }

    return 0;
}
