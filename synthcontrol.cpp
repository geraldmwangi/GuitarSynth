#include "synthcontrol.h"
#include <QVBoxLayout>


SynthControl::SynthControl(FloatInControl control,QWidget *parent) :
    QWidget(parent)
{
    mControl=control;
    //QString contname=QString::fromStdString(control->GetName());
    this->mknoblabel=new QLabel();
    this->mknob=new QDial();
    mknoblabel->setText(control.name);
    mknob->setMinimumSize(40,40);
    mknob->setMaximumSize(40,40);
    QFontMetrics fm(mknoblabel->font());
    int textlen=fm.width(control.name);
    mknoblabel->setMinimumSize(textlen,10);
    mknoblabel->setMaximumSize(textlen,10);
    QVBoxLayout* vbox=new QVBoxLayout(this);
    vbox->addWidget(mknoblabel);
    vbox->addWidget(mknob);
    this->setLayout(vbox);

    this->setMinimumSize(40,50);
    this->setMaximumSize(40,50);
    vbox->setSizeConstraint(QLayout::SetMinAndMaxSize);

//    this->mknob->setKnobMode(QSynthKnob::AngularMode);
    QObject::connect(this->mknob,SIGNAL(valueChanged(int)),this,SLOT(valChanged(int)));
    mknob->setRange(0,100);
    int val=100*(*(control.var)-control.min)/(control.max-control.min);
    mknob->setValue(val);
    //QObject::connect(mknob,SIGNAL(actionTriggered(int)))



}

SynthControl::~SynthControl()
{
    //delete mControl;
}

void SynthControl::valChanged(int val)
{
    float fval=mControl.min+((float)val*(mControl.max-mControl.min))/(100);
    *(mControl.var)=fval;
    if(mControl.update)
    {
        emit updateWaveTableSignal();
    }
}

void SynthControl::setToDefault()
{
    *(mControl.var)=mControl.defaultVal;
    int val=(mControl.defaultVal-mControl.min)*100/(mControl.max-mControl.min);
    mknob->setValue(val);
}


