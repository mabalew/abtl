/*
 * =====================================================================================
 *
 *       Filename:  traffic_lights.c
 *
 *    Description:  Simulation of traffic lights.
 *
 *        Version:  1.0
 *        Created:  05.02.2014 11:03:18
 *       Compiler:  avr-gcc
 *
 *         Author:  Mariusz
 *
 * =====================================================================================
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "traffic_lights.h"

// leds
#define LED_RED PB0
#define LED_YELLOW PB1
#define LED_GREEN PB2
#define RED_ON_TIME 4
#define YELLOW_ON_TIME 2
#define GREEN_ON_TIME 4

// initial timer value
#define timer_start 131

enum leds_enum {
  RED = 0,
  YELLOW = 1,
  GREEN = 2
} LEDS;

short led_states[3] = {1, 0, 0};;
short led_time[3] = {RED_ON_TIME, YELLOW_ON_TIME, GREEN_ON_TIME};
short emergency_state = 0;

volatile uint8_t counter = 0;

void init(void) {
  DDRB  |= (1 << LED_RED) | (1 << LED_YELLOW) | (1 << LED_GREEN);
  PORTB |= (1 << LED_RED);

  TIMSK0 |= (1 << OCIE0A);
  TCCR0A |= (1 << WGM01);
  TCNT0 = timer_start;

  sei();
}

int main(void0) {
  init();
  while (1);

  return 0;
}

ISR(TIM0_COMPA_vect) {
  TCNT0 = timer_start;
  counter++;
  verify_lights();
}

ISR(INT0_vect) {
  lights_off();
  emergency_switch();
  emergency_mode();
}

short is_led_on(enum leds_enum led) {
  return led_states[led];
}

void verify_lights() {
  if (emergency_state) {
    emergency_mode();
  } else {
    normal_mode();
  }
}

void normal_mode() {
  if (is_led_on(RED) && counter > led_time[RED]) {
    red_off();
    if (is_led_on(YELLOW)) {
      yellow_off();
    }
    green_on();
    counter = 0;
  } else if (is_led_on(RED) && counter > (led_time[RED] - led_time[YELLOW]) && counter <= led_time[RED]) {
    yellow_on();
  } else if (is_led_on(YELLOW) && counter > led_time[YELLOW]) {
    yellow_off();
    if (is_led_on(RED)) {
      red_off();
      green_on();
    } else if (is_led_on(GREEN)) {
      green_off();
      red_on();
    }
    counter = 0;
  } else if (is_led_on(GREEN) && counter > (led_time[GREEN])) {
    green_off();
    yellow_on();
    counter = 0;
  }
}

void emergency_mode() {
  if (counter > led_time[YELLOW]) {
    yellow_switch();
  }
}

void yellow_switch() {
  if (is_led_on(YELLOW)) {
    yellow_off();
  } else {
    yellow_on();
  }
}

void emergency_switch() {
  if (emergency_state == 0) {
    emergency_state = 1;
  } else {
    emergency_state = 0;
  }
}

void lights_off() {
  red_off();
  yellow_off();
  green_off();
}

void red_on() {
  PORTB |= (1 << LED_RED);
  led_states[RED] = 1;
}

void red_off() {
  PORTB &= ~(1 << LED_RED);
  led_states[RED] = 0;
}

void yellow_on() {
  PORTB |= (1 << LED_YELLOW);
  led_states[YELLOW] = 1;
}

void yellow_off() {
  PORTB &= ~(1 << LED_YELLOW);
  led_states[YELLOW] = 0;
}

void green_on() {
  PORTB |= (1 << LED_GREEN);
  led_states[GREEN] = 1;
}

void green_off() {
  PORTB &= ~(1 << LED_GREEN);
  led_states[GREEN] = 0;
}
