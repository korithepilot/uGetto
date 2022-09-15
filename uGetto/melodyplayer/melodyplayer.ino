static uint8_t i;
static uint8_t j;

#define T_MIN 17
#define  BUZZER_PIN  PB0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//#include "original_sound.h"

#include "sound_type.h"
#include "sound_constants.h"
#include "sound_generation.h"
#include "rick.h"

int main(void)
{
	DDRB = 0b00000001; // set BUZZER pin as OUTPUT
	PORTB = 0b00000000; // set all pins to LOW
	TCCR0A |= (1<<WGM01); // set timer mode to Fast PWM
	TCCR0A |= (1<<COM0A0); // connect PWM pin to Channel A of Timer0

		_delay_ms(2000);
    
	// Walk through all octaves
	for (i = 3; i < 8; ++i) {
		for (j = 0; j < 12; ++j)
            playNote(12*i+j, 8);

		_delay_ms(2000);
	}

	stop();
	 _delay_ms(1500);

	while (1) {
		for(j = 0; j < SONGLENGTH; j++)
			playNote(song[j]);
        _delay_ms(5000);
	}

}
