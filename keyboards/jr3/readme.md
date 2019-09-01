Jeff Roush's keyboard
======================

## Keyboard with optical switches

I'm calling this version of the firmware jr_optical.

The hardware of the matching keyboard is the latest iteration of my keyboards, version something-or-other. But the firmware is version 3.

The keyboard currently runs on a [Teensy 2.0 board](https://www.pjrc.com/store/teensy.html).

## Building

Run `make jr_optical:default && ./program` from the qmk root directory.

## Programming

I'm using the [teensy_loader_cli](https://www.pjrc.com/teensy/loader_cli.html) to program the Teensy.

On my Ubuntu 19.04 box, I did have to update the udev rules, as per the teensy documentation. I then built teensy_loader_cli, and added it to the path.

Then, put the teensy in program mode and run the `program` script in this directory.

## Notes

This was originally copied from the Bantam44 keyboard.

The keycodes are defined in tmk_core/common/keycode.h.

## On arch:

Install avr gcc and libc:

```
$ sudo pacman -S avr-gcc avr-libc
```
