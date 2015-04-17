#ifndef SYNTHCONTROL_H
#define SYNTHCONTROL_H

#include <QObject>
#include <QLabel>
#include <QtWidgets/QDial>
//#include <CLAM/qtmonitors/QSynthKnob.hxx>




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
