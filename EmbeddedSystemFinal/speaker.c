#include "speaker.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>

int freq[25];
unsigned char waveform[SAMPLE_RATE/2];
const int mid_a_freq = 440;
int phase_accumulator = 0;
int frequency = 0;

ISR(TIMER1_COMPA_vect){
    //this is called SAMPLE_RATE times per second
    //in here we want to update OCR2 -- update the current sample on the PWM
    phase_accumulator = (phase_accumulator + frequency) % SAMPLE_RATE;

    if(phase_accumulator < (SAMPLE_RATE/2))//first half
    {
        OCR2 = waveform[phase_accumulator];
    }
    else{//second half
        OCR2 = 255 - waveform[phase_accumulator - (SAMPLE_RATE/2)];
    }
    TCNT1 = 0;
}

void InitSpeaker() {
   TCCR2 |= (1 << 6) | (1 << 3);//We want FAST PWN mode
   TCCR2 |= (1 << 5);//COM21 = 1
   TCCR2 &= ~(1 << 4);//COM20 = 0 (non-inverting PWM)
   TCCR2 = (TCCR2 | 0x01);//No prescaler (as fast as possible)

        // Set initial pulse width = 0
   OCR2 = 0;

   SREG &= ~(1 << 7);//disable interrupt
   // Set CTC mode (Clear Timer on Compare Match) (p.133)
   // Have to set OCR1A *after*, otherwise it gets reset to 0!
   TCCR1A = 0;
   TCCR1B = 0 | (0 << 4) | (1 << 3) | 1;//CTC mode on Timer1, no prescaler

        //Set CTC mode
   TIMSK |= (1 << 4);
        //Now make sure timer1 interrupt is fired at the sample rate
   OCR1A = F_CPU / SAMPLE_RATE;

   buildFreqs();
   buildWaveform();

}

void buildWaveform(){
    int i;
    for(i = 0; i < SAMPLE_RATE/2; ++i){
        waveform[i] = (unsigned char)(((sin( ((double)i / (SAMPLE_RATE/2)) * M_PI )) * 127.5) + 127.5);
    }
}

void buildFreqs(){
        double temp_freq = 0;
        int final_freq = 0;
        double sq2 = pow(2.0, (1.0/12.0));
        int i;
        for(i = 0; i < 25; i++)
        {
                temp_freq = mid_a_freq * pow(sq2, (i - 12));
                final_freq = ceil(temp_freq);
                freq[i] = final_freq;
        }
}

void SetFrequency(int val) {
   frequency = freq[val];
}
void Clr_Freq()
{
	frequency = 0;
}
