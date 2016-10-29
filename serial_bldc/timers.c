#include "timers.h"
#include <avr/io.h>

void timer1_stop(void) {
    TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
}

void timer1_start(void) {
    TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));

    /* prescaler is divide by 64 */
    TCCR1B |= (0<<CS12) | (1<<CS11) | (1<<CS10);
    #define F_TC0 (F_CPU/64UL)
}

void timer1_reset(void) {
    TCNT1 = 0;
}

void setup_timer1(void) {
    /* FastPWM mode, count up to ICR1 */
    TCCR1A = (1<<WGM11) | (0<<WGM10);
    TCCR1B = (1<<WGM13) | (1<<WGM12);
    /* OC1A is set on TOP, cleared on compare */
    TCCR1A |= (1<<COM1A1) | (0<<COM1A0);
    /* OC1B is set on TOP, cleared on compare */
    TCCR1A |= (1<<COM1B1) | (0<<COM1B0);
    /* OC1C is set on TOP, cleared on compare */
    TCCR1A |= (1<<COM1C1) | (0<<COM1C0);

    timer1_stop();
    timer1_reset();

    /* 20ms frame time (50fps) */
    ICR1 = F_TC0/50;
    /* initally 1ms, which is the minimum  pulse length for a servo */
    OCR1A = F_TC0/1000UL;
    OCR1B = F_TC0/1000UL;
    OCR1C = F_TC0/1000UL;

    /* interrupts are disabled for now */
    TIMSK0 = 0;
}

void Timers_Init(void) {
    setup_timer1();
}
