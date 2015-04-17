#ifndef SYNTHBASE_H
#define SYNTHBASE_H
/*
This file is part of GuitarSynth2.

    GuitarSynth2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GuitarSynth2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GuitarSynth2.  If not, see <http://www.gnu.org/licenses/>.
    */
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
