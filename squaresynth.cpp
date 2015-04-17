#include "squaresynth.h"
#include <math.h>

SquareSynth::SquareSynth(QWidget* parent):
    SynthBase(parent,"SquareSynth")
{
}

void SquareSynth::InitSynth()
{


    float steps=mWaveTableSize/4*radius;

    for(int i=0;i<steps;i++)
    {
        mWaveTable[i]=1.0f-(1.0f-i/steps)*radius;
        mWaveTable[i+mWaveTableSize/2]=-mWaveTable[i];
    }
    for(int i=steps;i<=mWaveTableSize/2-steps;i++)
    {
        mWaveTable[i]=1;
        mWaveTable[i+mWaveTableSize/2]=-mWaveTable[i];
    }
    for(int i=mWaveTableSize/2-steps;i<mWaveTableSize/2;i++)
    {
        mWaveTable[i]=1.0f-(1.0f-(mWaveTableSize/2-i)/steps)*radius;
        mWaveTable[i+mWaveTableSize/2]=-mWaveTable[i];
    }






}

void SquareSynth::InitControls()
{
    radius=0;
    addControl("Radius",radius,0,1,true);
}
