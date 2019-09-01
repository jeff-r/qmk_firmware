/*

Copyright 2019 Jeff Roush <jeff@jeffroush.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "jr_optical.h"
#include <string.h>

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

#define LEDS_ON_JEFF  (PORTB = 0b01110000)
#define LEDS_OFF_JEFF (PORTB = 0)

#define IR_LED_ON     (PORTB |=  (1<<5))
#define IR_LED_OFF    (PORTB &= ~(1<<5))

#define GREEN_LED_ON     (PORTB |=  (1<<4))
#define GREEN_LED_OFF    (PORTB &= ~(1<<4))

#define IR_BEAM_STATE    (PINC & (1<<7))

#define LED_CONFIG_B  (DDRB  = 0b01110000)
#define LED_CONFIG_C  (DDRC &= ~(1<<7))

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))


__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
  LED_CONFIG_B;
  LED_CONFIG_C;
  LEDS_ON_JEFF;
  IR_LED_ON;
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void)
{
  matrix_init_quantum();
}

void show_interrupted_beam(void)
{
  if (IR_BEAM_STATE)
  {
    GREEN_LED_OFF;
    matrix[0] = 0;
  }
  else
  {
    GREEN_LED_ON;
    matrix[0] = 1;
  }
}

uint8_t matrix_scan(void)
{
  show_interrupted_beam();

  return 1;
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
}