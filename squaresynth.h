#ifndef SQUARESYNTH_H
#define SQUARESYNTH_H
#include "synthbase.h"


class SquareSynth : public SynthBase
{


public:
    SquareSynth(QWidget* parent);

    virtual void InitSynth();
    virtual void InitControls();
private:
    float radius;
};

#endif // SQUARESYNTH_H
