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

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "split_util.h"
#include "config.h"
#include "quantum.h"
#include "debounce.h"
#include "transport.h"




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

bool is_keyboard_right(void);
bool is_keyboard_left(void);
bool is_keyboard_master(void);




// // row offsets for each hand
uint8_t thisHand, thatHand;

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

#define ERROR_DISCONNECT_COUNT 5


/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
// static matrix_row_t raw_matrix[ROWS_PER_HAND];

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


void matrix_init_kb(void) {
  matrix_init_user();
  LED_CONFIG_B;
  LED_CONFIG_C;
  LEDS_ON_JEFF;
  IR_LED_ON;
  PORTD |= 1;
  debug_enable = true;
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

void blink(void)
{
  GREEN_LED_OFF;
  matrix[0] = 0;
  wait_ms(100);
  GREEN_LED_ON;
  matrix[0] = 1;
  wait_ms(100);
}


bool toggle_on = false;

void toggle_letter(bool toggle) {
  if (is_keyboard_left())
    return;

  if (toggle) {
    matrix[0] = 0;
    matrix[1] = 0;
  } else {
    matrix[0] = 2;
    matrix[1] = 2;
  }
}

void right_side_matrix_scan(void) {
  if (IR_BEAM_STATE)
    matrix[1] = 0;
  else
    matrix[1] = 1;
}

void toggle_led(bool toggle) {
  if (toggle) {
    GREEN_LED_OFF;
  } else {
    GREEN_LED_ON;
  }
}

void toggles(void)
{
  uprintf("toggle_on: %d\n", toggle_on);
  toggle_led(toggle_on);
  // right_side_matrix_scan();
  // toggle_letter(toggle_on);
  toggle_on = !toggle_on;
}


int timer_counter;

bool initialized_matrix = false;

bool check_matrix(void) {
  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    if (matrix[current_row])
      return true;
  }
  return false;
}

void matrix_init(void)
{
  if (initialized_matrix)
    return;

  matrix_init_quantum();
  thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
  thatHand = ROWS_PER_HAND - thisHand;

  initialized_matrix = true;
  if (is_keyboard_master()) {
    transport_master_init();
  } else {
    transport_slave_init();
  }
  timer_counter = 0;
  toggle_on = false;
}

bool showed_info = false;
int tick_counter = 0;

void show_info(bool force) {

  if (force || !showed_info)
    for(int i = 0; i < MATRIX_ROWS; i++) {
      uprintf("matrix[%d] = %d\n", i, matrix[i]);
    }
  showed_info = true;
}

void tick(void)
{
  if (!initialized_matrix)
    return;

  right_side_matrix_scan();
  timer_counter++;
  if (timer_counter > 20000) {
    show_info(true);
    timer_counter = 0;
    toggles();
  }
}

uint8_t _matrix_scan(void) {
  bool changed = false;
  tick();

  return (uint8_t)changed;
}

uint8_t matrix_scan(void) {
  uint8_t ret = _matrix_scan();

  if (is_keyboard_master()) {
    static uint8_t error_count;

    if (!transport_master(matrix + thatHand)) {
      error_count++;

      if (error_count > ERROR_DISCONNECT_COUNT) {
                // reset other half if disconnected
        for (int i = 0; i < ROWS_PER_HAND; ++i) {
          matrix[thatHand + i] = 0;
        }
      }
    } else {
      error_count = 0;
    }

    // matrix_scan_quantum();
  } else {
    transport_slave(matrix + thisHand);
  }

  return ret;
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
}
