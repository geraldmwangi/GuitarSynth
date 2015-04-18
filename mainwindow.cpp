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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "squaresynth.h"
#include "sinussynth.h"
#include "gausssynth.h"
#include <sawsynth.h>
#include <QVBoxLayout>
#include <strstream>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SynthArea->setWidget(new QWidget);
    ui->SynthArea->widget()->setMinimumWidth(ui->SynthArea->width());
    ui->SynthArea->widget()->setMaximumWidth(ui->SynthArea->width());
    ui->SynthArea->widget()->setMinimumHeight(0);
    ui->SynthArea->widget()->setMaximumHeight(0);
    ui->SynthArea->widget()->setLayout(new QVBoxLayout);


    mEngine=new GSEngine(this);
    InitSignalSlots();
    mEngine->addSynth(new SinusSynth(ui->SynthArea->widget()));
    mEngine->addSynth(new SinusSynth(ui->SynthArea->widget()));
    mEngine->addSynth(new SawSynth(ui->SynthArea->widget()));
    mEngine->addSynth(new SawSynth(ui->SynthArea->widget()));
    mEngine->addSynth(new SquareSynth(ui->SynthArea->widget()));

    mEngine->addSynth(new SquareSynth(ui->SynthArea->widget()));
    mEngine->addSynth(new GaussSynth(ui->SynthArea->widget()));
    mEngine->addSynth(new GaussSynth(ui->SynthArea->widget()));



    mEngine->StartEngine();
    //mEngine->saveEngineNet("/home/gerald/clamtest/testguitsynth.clamnetwork");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitSignalSlots()
{
    QObject::connect(mEngine,SIGNAL(freqChanged(float)),this,SLOT(updateFreqLabel(float)));
    QObject::connect(ui->InputVol,SIGNAL(valueChanged(int)),mEngine,SLOT(setInputGain(int)));

    QObject::connect(ui->OutputVol,SIGNAL(valueChanged(int)),mEngine,SLOT(setOutputGain(int)));
    ui->InputVol->setValue(99);
    ui->OutputVol->setValue(99);
}

QWidget * MainWindow::getSynthArea()
{
    return ui->SynthArea;
}

void MainWindow::updateFreqLabel(float val)
{
    strstream t;
    t<<val<<std::endl;
    ui->freqLab->setText(QString::fromStdString(t.str()));
}
