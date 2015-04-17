#ifndef SYNTHBASE_H
#define SYNTHBASE_H

#include <QWidget>
#include <gsengine.h>
#include <synthcontrol.h>
#define BASE_FREQ 180.0f
using namespace std;
namespace Ui {
    class SynthBase;
}

class SynthBase : public QWidget
{
    Q_OBJECT
public:
    explicit SynthBase(QWidget* parent,QString name);
    void setSamplerate(int sr);
    void setBufferSize(int bs);
    ~SynthBase();

    void InitBaseSynth();
    virtual void InitSynth()=0;
    virtual void InitControls();
    void addControl(FloatInControl control);
    void addControl(QString name,float& val,float min, float max,bool update=false);

    void process(int frames, float* buffer,float freq);


signals:

public slots:
    void updateWaveTable();
protected:
    float phase;
    float ampl;
    float transposefactor;

    float curFreq;
    float curTablePos;
    float* mWaveTable;
    float* mWindow;

    int mWaveTableSize;
    int mBufferSize;
    int mSamplerate;
    string mSynthname;

private:
    Ui::SynthBase *ui;



};

#endif // SYNTHBASE_H
