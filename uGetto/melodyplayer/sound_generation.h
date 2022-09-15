static inline void tone(uint8_t noteNum)
{
	TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | compares[noteNum];
  	OCR0A =  (noteNum <= 23) ? N_64 : N_8 - 1; // set the OCRnx
}

static inline void stop(void)
{

	TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
}

static void inline playNote(const uint8_t& noteNum, const int& duration_cycles)
{
    if(noteNum == 255)
    {
	    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
    }
    else
    {
	    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | compares[noteNum];
  	    OCR0A =  (noteNum <= 23) ? N_64 : N_8 - 1;
    }

    i = duration_cycles;
    while(i-- > 0)
    {
        _delay_ms(T_MIN);
    }
}

static void inline playNote(const Sound& s)
{
    if(s.noteNum == 255)
    {
	    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
    }
    else
    {
	    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | compares[s.noteNum];
  	    OCR0A =  (s.noteNum <= 23) ? N_64 : N_8 - 1;
    }

    i = s.duration_cycles;
    while(i-- > 0)
    {
        _delay_ms(T_MIN);
    }
}
