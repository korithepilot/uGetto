static uint8_t i;
static uint8_t j;
static  uint8_t comp;

#define T_MIN 76
#define  BUZZER_PIN  PB0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//#include "original_sound.h"

#include "sound_type.h"
#include "sound_constants.h"
#include "sound_generation.h"
#include "rick_new.h"


uint8_t playing = 0;

  uint8_t k = 0;

int main(void)
{
  DDRB = 0b00000001; // set BUZZER pin as OUTPUT
  PORTB = 0b00000000; // set all pins to LOW
  TCCR0A |= (1<<WGM01); // set timer mode to Fast PWM
  TCCR0A |= (1<<COM0A0); // connect PWM pin to Channel A of Timer0

  DDRB |= 1 << DDB4;     // define PB4 - LED as output
  DDRB &= ~ (1 << DDB3); // define PB3 as input 

  GIMSK |= 1 << PCIE;       // enable PCINT[0:5] pin change interrupt
  PCMSK |= 1 << PCINT3;     // configure interrupt at PB3

  PORTB |= 1 << PB3;    // enable pull up resistor at PB1
  sei();   


  uint8_t noteNum;
  uint8_t dur;



  
  _delay_ms(1000);

  while (1) {

    if (playing == 1) {
      PORTB &= ~(1 << PB4);
      noteNum = pgm_read_byte_near(song + k);
       dur = pgm_read_byte_near(song + k + 1);
      playNote(noteNum, dur);
      k = k+2 < SONGLENGTH ? k+2 : 0;
   }
   else {
       PORTB |= 1 << PB4;
    }
    

  }


  
}

uint8_t read_pin(uint8_t pin) {
  return (PINB & (1 << pin)) >> pin; 
}


uint8_t is_button_pressed(uint8_t pin) {

   if (!read_pin(PB3)) {    
    _delay_ms(50);
   if (!read_pin(PB3)) {
        return 1;
      } 
   }
   return 0;
  
}






ISR(PCINT0_vect) {
   
   if (is_button_pressed(PB3)) { 
   }
   else  {
    
    k = 0;
    playing = 1- playing;
    stop();
   }
}
