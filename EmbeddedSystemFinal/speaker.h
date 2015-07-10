#ifndef __speaker_h__
#define __speaker_h__

#define F_CPU 8000000UL
#define SAMPLE_RATE 2000

void InitSpeaker();
void buildWaveform();
void buildFreqs();
void SetFrequency(int);
void Clr_Freq();
#endif
