#ifndef GAUSSSYNTH_H
#define GAUSSSYNTH_H
#include "synthbase.h"

class GaussSynth : public SynthBase
{
public:
    GaussSynth(QWidget* parent);
    virtual void InitSynth();
    virtual void InitControls();
private:
    float sdfactor;
};

#endif // GAUSSSYNTH_H
