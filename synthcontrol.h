#ifndef SYNTHCONTROL_H
#define SYNTHCONTROL_H
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
#include <QObject>
#include <QLabel>
#include <QDial>




struct FloatInControl
{
    QString name;
    float defaultVal;
    float *var;
    float min;
    float max;
    bool update;

};


class SynthControl : public QWidget
{
    Q_OBJECT
public:
    explicit SynthControl(FloatInControl control,QWidget *parent = 0);
    ~SynthControl();


signals:

    void updateWaveTableSignal();
public slots:
    void valChanged(int val);
    void setToDefault();
private:
    QDial* mknob;
    QLabel* mknoblabel;

    FloatInControl mControl;
    float mMin,mMax;

};

#endif // SYNTHCONTROL_H
