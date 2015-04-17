#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "squaresynth.h"
#include "sinussynth.h"
#include "gausssynth.h"
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
