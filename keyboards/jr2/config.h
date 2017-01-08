/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Bantam Keyboards
#define PRODUCT         Bantam44
#define DESCRIPTION     A custom keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16



// Columns to pins
// These are all outputs
// V0  B0
// V1  B1
// V2  B2
// V3  B3
// V4  B7
// V5  D0
// V6  D1
// V7  D2
// V8  D3
// V9  C6
// V10 C7
// V11 D5
// V12 D4
// V13 D6
// V14 D7
// V15 B4
// V16 B5

// Rows to pins
// These are all inputs
// H0 F0
// H1 F1
// H2 F4
// H3 F5
// H4 F6
// H5 F7

// Planck PCB default pin-out
// Change this to how you wired your keyboard
// COLS: Left to right, ROWS: Top to bottom
#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { B4, D7, D6, D4, D5, C7, C6, D3, D2, D1, D0, B7, B3, B2, B1, B0, B5 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */
/* Locking resynchronize hack */
/* #define LOCKING_RESYNC_ENABLE */

/* key combination for command */

#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
