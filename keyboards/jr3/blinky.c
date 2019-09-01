#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usb_debug_only.h"
#include "print.h"

void run();
void set_green_led();

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


int main(void)
{
  // set for 16 MHz clock, and make sure the LED is off
  CPU_PRESCALE(0);
  LED_CONFIG_B;
  LED_CONFIG_C;
  LEDS_ON_JEFF;

  while (1) {
    run();
  }
}

void run()
{
  IR_LED_OFF;
  GREEN_LED_OFF;
  _delay_ms(1000);
  IR_LED_ON;
  _delay_us(290);
  show_detected_beam();
  _delay_ms(2000);
}

void show_detected_beam()
{
  if (IR_BEAM_STATE)
    GREEN_LED_ON;
  else
    GREEN_LED_OFF;
  _delay_ms(50);
}

void show_interrupted_beam()
{
  if (IR_BEAM_STATE)
    GREEN_LED_OFF;
  else
    GREEN_LED_ON;
  _delay_ms(50);
}
