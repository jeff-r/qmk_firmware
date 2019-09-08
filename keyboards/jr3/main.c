/*
 * Copyright 2012 Jun Wako <wakojun@gmail.com>
 * This file is based on:
 *     LUFA-120219/Demos/Device/Lowlevel/KeyboardMouse
 *     LUFA-120219/Demos/Device/Lowlevel/GenericHID
 */

/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "sendchar.h"
#include "debug.h"
#include "suspend.h"

#include "lufa.h"


bool is_keyboard_right(void);
bool is_keyboard_left(void);
bool is_keyboard_master(void);


bool is_keyboard_right(void) {
    return !is_keyboard_left();
}

bool is_keyboard_master(void) {
    return is_keyboard_left();
}



/*******************************************************************************
 * main
 ******************************************************************************/
/** \brief Setup MCU
 *
 * FIXME: Needs doc
 */
static void setup_mcu(void) {
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    // clock_prescale_set(clock_div_1);

    CLKPR = (1 << CLKPCE);
    CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
}



/** \brief Setup USB
 *
 * FIXME: Needs doc
 */
static void setup_usb(void) {
    if (is_keyboard_right())
        return;

    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar);
}

/** \brief Main
 *
 * FIXME: Needs doc
 */
int main(void) {

    setup_mcu();
    keyboard_setup();
    setup_usb();
    sei();

    USB_USBTask();
    /* init modules */
    keyboard_init();
    host_set_driver(&lufa_driver);

    print("Keyboard start.\n");
    dprintf("***********************\n");
    while (1) {

        keyboard_task();

        USB_USBTask();
    }
}

