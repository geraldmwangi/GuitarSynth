#include "gausssynth.h"
#include <math.h>

GaussSynth::GaussSynth(QWidget* parent):
    SynthBase(parent,"GaussSynth")
{
}

void GaussSynth::InitSynth()
{
    float sd=(mWaveTableSize-1)/(2.0f*sdfactor);
    sd=sd*sd;
    float norm=0;
    float mu=(mWaveTableSize-1)/2.0f;

    for(int i=0;i<mWaveTableSize;i++)
        mWaveTable[i]=exp(-(i-mu)*(i-mu)/(2*sd));
}

void GaussSynth::InitControls()
{
    sdfactor=2;
    addControl("Formfactor",sdfactor,0.1,10,true);
}
