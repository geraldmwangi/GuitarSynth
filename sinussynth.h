#ifndef SINUSSYNTH_H
#define SINUSSYNTH_H
#include "synthbase.h"
class SinusSynth : public SynthBase
{
public:
    SinusSynth(QWidget* parent);
    virtual void InitSynth();
};

#endif // SINUSSYNTH_H
