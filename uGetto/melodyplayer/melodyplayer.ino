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

int main(void)
{
	DDRB = 0b00000001; // set BUZZER pin as OUTPUT
	PORTB = 0b00000000; // set all pins to LOW
	TCCR0A |= (1<<WGM01); // set timer mode to Fast PWM
	TCCR0A |= (1<<COM0A0); // connect PWM pin to Channel A of Timer0


  uint8_t noteNum;
  uint8_t dur;
  
	_delay_ms(1000);

  for(j = 0; j < SONGLENGTH; j += 2)
  {
    noteNum = pgm_read_byte_near(song + j);
    dur = pgm_read_byte_near(song + j + 1);
    playNote(noteNum, dur);
    playNote(NOTE_STOP, 1);
  }


  /*

  uint32_t ret;
  Sound *val;
  ret = pgm_read_word_near((uint8_t *)&song + 0);
  val = (Sound *)&ret;
  uint8_t note = val->noteNum;
  uint8_t dur = val->duration_cycles;
  
  playNote(note, dur);

  */
  /*
  for(int a = 0; a < SONGLENGTH; a++)
  {
    uint8_t noteNum = song[a].noteNum;
    uint8_t dur = song[a].duration_cycles;
    playNote(&noteNum, &dur);
  }
  */

   /*
	// Walk through all octaves
	for (i = 3; i < 8; ++i) {
		for (j = 0; j < 12; ++j)
            playNote(12*i+j, 8);

		_delay_ms(2000);
	}
  
  
	stop();
	 _delay_ms(1500);

	while (1) {
        _delay_ms(5000);
	}
  */
}
