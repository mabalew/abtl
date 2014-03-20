/*
 * =====================================================================================
 *
 *       Filename:  traffic_lights.h
 *
 *    Description:  Simulation of traffic lights headers.
 *
 *        Version:  1.0
 *        Created:  21.01.2014 08:18:24
 *       Compiler:  avr-gcc
 *
 *         Author:  Mariusz
 *
 * =====================================================================================
 */
#ifndef _TRAFFIC_LIGHTS_H
#define _TRAFFIC_LIGHTS_H

#define LED_RED PB0
#define LED_YELLOW PB1
#define LED_GREEN PB2

// Time (ms) to show red light
const int RED_ON_TIME=40;

// Time (ms) to show yellow light
const int YELLOW_ON_TIME=10;

// Time (ms) to show green light
const int GREEN_ON_TIME=40;

// Time (ms) show red and yellow lights together
const int RED_AND_YELLOW_TOGETHER_TIME=10;

// Initialization of the microcontroller and light
void init();

void red_on();
void red_off();
void yellow_on();
void yellow_off();
void yellow_switch();
void green_on();
void green_off();
void lights_off();
void verify_lights();
void normal_mode();
void emergency_mode();
void emergency_switch();

#endif
