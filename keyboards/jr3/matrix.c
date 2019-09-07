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

void toggle_led(void)
{
  GREEN_LED_OFF;
  matrix[0] = 0;
  wait_ms(100);
  GREEN_LED_ON;
  matrix[0] = 1;
  wait_ms(100);
}


void matrix_init(void)
{
  matrix_init_quantum();
  thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
  thatHand = ROWS_PER_HAND - thisHand;

  if (is_keyboard_master()) {
    transport_master_init();
  } else {
    transport_slave_init();
  }
  toggle_led();
  toggle_led();
  toggle_led();
  toggle_led();
}

void show_interrupted_beam(void)
{
  if (IR_BEAM_STATE)
  {
    GREEN_LED_ON;
    matrix[0] = 0;
  }
  else
  {
    GREEN_LED_OFF;
    matrix[0] = 1;
  }
}

// uint8_t matrix_scan(void)
// {
//   // show_interrupted_beam();
// 
//   return 1;
// }


uint8_t _matrix_scan(void) {
    bool changed = false;

    // if (!isLeftHand)
      // show_interrupted_beam();
      toggle_led();

    // Set col, read rows
    // for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
    //     changed |= read_rows_on_col(raw_matrix, current_col);
    // }

    // debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed);

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

    matrix_scan_quantum();
  } else {
    // transport_slave(matrix + thisHand);
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




// *************************************************************************

// #if (MATRIX_COLS <= 8)
// #    define print_matrix_header() print("\nr/c 01234567\n")
// #    define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
// #    define matrix_bitpop(i) bitpop(matrix[i])
// #    define ROW_SHIFTER ((uint8_t)1)
// #elif (MATRIX_COLS <= 16)
// #    define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
// #    define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
// #    define matrix_bitpop(i) bitpop16(matrix[i])
// #    define ROW_SHIFTER ((uint16_t)1)
// #elif (MATRIX_COLS <= 32)
// #    define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
// #    define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
// #    define matrix_bitpop(i) bitpop32(matrix[i])
// #    define ROW_SHIFTER ((uint32_t)1)
// #endif
// 
// #define ERROR_DISCONNECT_COUNT 5
// 
// #define ROWS_PER_HAND (MATRIX_ROWS / 2)
// 
// static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
// static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
// 
// /* matrix state(1:on, 0:off) */
// static matrix_row_t matrix[MATRIX_ROWS];
// static matrix_row_t raw_matrix[ROWS_PER_HAND];
// 
// // row offsets for each hand
// uint8_t thisHand, thatHand;
// 
// // user-defined overridable functions
// 
// __attribute__((weak)) void matrix_slave_scan_user(void) {}
// 
// // helper functions
// 
// inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }
// 
// inline uint8_t matrix_cols(void) { return MATRIX_COLS; }
// 
// bool matrix_is_modified(void) {
//     if (debounce_active()) return false;
//     return true;
// }

// inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

// matrix code

//  #ifdef DIRECT_PINS
//  
//  static void init_pins(void) {
//      for (int row = 0; row < MATRIX_ROWS; row++) {
//          for (int col = 0; col < MATRIX_COLS; col++) {
//              pin_t pin = direct_pins[row][col];
//              if (pin != NO_PIN) {
//                  setPinInputHigh(pin);
//              }
//          }
//      }
//  }
//  
//  static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
//      matrix_row_t last_row_value = current_matrix[current_row];
//      current_matrix[current_row] = 0;
//  
//      for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
//          pin_t pin = direct_pins[current_row][col_index];
//          if (pin != NO_PIN) {
//              current_matrix[current_row] |= readPin(pin) ? 0 : (ROW_SHIFTER << col_index);
//          }
//      }
//  
//      return (last_row_value != current_matrix[current_row]);
//  }
//  
//  #elif (DIODE_DIRECTION == COL2ROW)
//  
//  static void select_row(uint8_t row) {
//      setPinOutput(row_pins[row]);
//      writePinLow(row_pins[row]);
//  }
//  
//  static void unselect_row(uint8_t row) { setPinInputHigh(row_pins[row]); }
//  
//  static void unselect_rows(void) {
//      for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
//          setPinInputHigh(row_pins[x]);
//      }
//  }
//  
//  static void init_pins(void) {
//      unselect_rows();
//      for (uint8_t x = 0; x < MATRIX_COLS; x++) {
//          setPinInputHigh(col_pins[x]);
//      }
//  }
//  
//  static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
//      // Store last value of row prior to reading
//      matrix_row_t last_row_value = current_matrix[current_row];
//  
//      // Clear data in matrix row
//      current_matrix[current_row] = 0;
//  
//      // Select row and wait for row selecton to stabilize
//      select_row(current_row);
//      wait_us(30);
//  
//      // For each col...
//      for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
//          // Populate the matrix row with the state of the col pin
//          current_matrix[current_row] |= readPin(col_pins[col_index]) ? 0 : (ROW_SHIFTER << col_index);
//      }
//  
//      // Unselect row
//      unselect_row(current_row);
//  
//      return (last_row_value != current_matrix[current_row]);
//  }
//  
//  #elif (DIODE_DIRECTION == ROW2COL)
//  
//  static void select_col(uint8_t col) {
//      setPinOutput(col_pins[col]);
//      writePinLow(col_pins[col]);
//  }
//  
//  static void unselect_col(uint8_t col) { setPinInputHigh(col_pins[col]); }
//  
//  static void unselect_cols(void) {
//      for (uint8_t x = 0; x < MATRIX_COLS; x++) {
//          setPinInputHigh(col_pins[x]);
//      }
//  }
//  
//  static void init_pins(void) {
//      unselect_cols();
//      for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
//          setPinInputHigh(row_pins[x]);
//      }
//  }
//  
//  static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
//      bool matrix_changed = false;
//  
//      // Select col and wait for col selecton to stabilize
//      select_col(current_col);
//      wait_us(30);
//  
//      // For each row...
//      for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
//          // Store last value of row prior to reading
//          matrix_row_t last_row_value = current_matrix[row_index];
//  
//          // Check row pin state
//          if (readPin(row_pins[row_index])) {
//              // Pin HI, clear col bit
//              current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
//          } else {
//              // Pin LO, set col bit
//              current_matrix[row_index] |= (ROW_SHIFTER << current_col);
//          }
//  
//          // Determine if the matrix changed state
//          if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
//              matrix_changed = true;
//          }
//      }
//  
//      // Unselect col
//      unselect_col(current_col);
//  
//      return matrix_changed;
//  }
//  
//  #endif

// void matrix_init(void) {
//     debug_enable = true;
//     debug_matrix = true;
//     debug_mouse  = true;
// 
//     // Set pinout for right half if pinout for that half is defined
//     if (!isLeftHand) {
// #ifdef DIRECT_PINS_RIGHT
//         const pin_t direct_pins_right[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS_RIGHT;
//         for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
//             for (uint8_t j = 0; j < MATRIX_COLS; j++) {
//                 direct_pins[i][j] = direct_pins_right[i][j];
//             }
//         }
// #endif
// #ifdef MATRIX_ROW_PINS_RIGHT
//         const pin_t row_pins_right[MATRIX_ROWS] = MATRIX_ROW_PINS_RIGHT;
//         for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
//             row_pins[i] = row_pins_right[i];
//         }
// #endif
// #ifdef MATRIX_COL_PINS_RIGHT
//         const pin_t col_pins_right[MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
//         for (uint8_t i = 0; i < MATRIX_COLS; i++) {
//             col_pins[i] = col_pins_right[i];
//         }
// #endif
//     }
// 
//     thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
//     thatHand = ROWS_PER_HAND - thisHand;
// 
//     // initialize key pins
//     init_pins();
// 
//     // initialize matrix state: all keys off
//     for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
//         matrix[i] = 0;
//     }
// 
//     debounce_init(ROWS_PER_HAND);
// 
//     matrix_init_quantum();
// }

// uint8_t _matrix_scan(void) {
//     bool changed = false;
// 
// #if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
//     // Set row, read cols
//     for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
//         changed |= read_cols_on_row(raw_matrix, current_row);
//     }
// #elif (DIODE_DIRECTION == ROW2COL)
//     // Set col, read rows
//     for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
//         changed |= read_rows_on_col(raw_matrix, current_col);
//     }
// #endif
// 
//     debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed);
// 
//     return (uint8_t)changed;
// }

// uint8_t matrix_scan(void) {
//     uint8_t ret = _matrix_scan();
// 
//     if (is_keyboard_master()) {
//         static uint8_t error_count;
// 
//         if (!transport_master(matrix + thatHand)) {
//             error_count++;
// 
//             if (error_count > ERROR_DISCONNECT_COUNT) {
//                 // reset other half if disconnected
//                 for (int i = 0; i < ROWS_PER_HAND; ++i) {
//                     matrix[thatHand + i] = 0;
//                 }
//             }
//         } else {
//             error_count = 0;
//         }
// 
//         matrix_scan_quantum();
//     } else {
//         transport_slave(matrix + thisHand);
//         matrix_slave_scan_user();
//     }
// 
//     return ret;
// }