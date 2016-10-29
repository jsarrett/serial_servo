#include "timers.h"
#include <avr/io.h>

void timer1_stop(void) {
    TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
}

void timer1_start(void) {
    TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));

    /* prescaler is divide by 1 */
    TCCR1B |= (0<<CS12) | (0<<CS11) | (1<<CS10);
}

void timer1_reset(void) {
    TCNT1 = 0;
}

void setup_timer1(void) {
    /* FastPWM mode, count up to OCR1A */
    TCCR1A = (1<<WGM11) | (1<<WGM10);
    TCCR1B = (1<<WGM13) | (1<<WGM12);
    /* OC1A is disabled */
    TCCR1A |= (0<<COM1A1) | (0<<COM1A0);
    /* OC1B is disabled */
    TCCR1A |= (0<<COM1B1) | (0<<COM1B0);
    /* OC1C is disabled */
    TCCR1A |= (0<<COM1C1) | (0<<COM1C0);

    timer1_stop();
    timer1_reset();

    /* initally 0 (disabled) */
    OCR1A = 0;

    /* interrupt on TOV (top) */
    TIMSK0 = _BV(TOIE1);
}

void Timers_Init(void) {
    setup_timer1();
}
