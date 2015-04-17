#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T16:19:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuitarSynth2
TEMPLATE = app
LIBS += -lclam_qtmonitors -lclam_processing -lclam_audioio -lclam_core -ljack -laubio

SOURCES += main.cpp\
        mainwindow.cpp \
    gausssynth.cpp \
    gsengine.cpp \
    sinussynth.cpp \
    squaresynth.cpp \
    synthbase.cpp \
    synthcontrol.cpp

HEADERS  += mainwindow.h \
    gausssynth.h \
    gsengine.h \
    sinussynth.h \
    squaresynth.h \
    synthbase.h \
    synthcontrol.h \
    widget.h

FORMS    += mainwindow.ui \
    SynthBase.ui

