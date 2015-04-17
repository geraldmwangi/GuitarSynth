#include "sinussynth.h"
#include <math.h>

SinusSynth::SinusSynth(QWidget* parent):
    SynthBase(parent,"SinusSynth")
{
}

void SinusSynth::InitSynth()
{

    for(int i=0;i<mWaveTableSize;i++)
        mWaveTable[i]=sin(2*M_PI*i/(mWaveTableSize));



}
