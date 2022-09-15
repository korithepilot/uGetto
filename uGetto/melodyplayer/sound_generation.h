static inline void stop(void)
{

	TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
}

static void inline playNote(const uint8_t& noteNum, const uint8_t& duration_cycles)
{
    if(noteNum == 255)
    {
	    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop
    }
    else
    {
      comp = pgm_read_byte_near( compares + noteNum);
	    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | ((noteNum <= 23) ? N_64 : N_8);  // set compare
  	  OCR0A =  comp - 1; // set the scaler
    }

    i = duration_cycles;
    while(i-- > 0)
    {
        _delay_ms(T_MIN); // _delay_ms needs a compile time constant, this is why it was done this way
    }
}

static void inline playNote(const Sound& s)
{
    if(s.noteNum == 255)
    {
	    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop
    }
    else
    {
      comp = pgm_read_byte_near( compares + s.noteNum);
	    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | ((s.noteNum <= 23) ? N_64 : N_8);  // set compare
  	  OCR0A =   comp - 1; // set the scaler
    }

    i = s.duration_cycles;
    while(i-- > 0)
    {
        _delay_ms(T_MIN);
    }
}
