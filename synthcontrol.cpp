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


