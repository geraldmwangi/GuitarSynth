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
#include "synthbase.h"
#include "gsengine.h"
#include <exception>
#include <iostream>
#include <math.h>

#include <QMessageBox>

GSEngine* GSEngine::mInstance=0;

GSEngine::GSEngine(QObject *parent) :
    QObject(parent)
{
    mInstance=this;
    InitNetwork();
    lastfreq=0;

}

GSEngine::~GSEngine()
{
    StopEngine();
    if(mInBuf)
        delete [] mInBuf;
    mInBuf=0;
    if(mOutBuf)
        delete [] mOutBuf;
    mOutBuf=0;

}

void GSEngine::InitNetwork()
{
    mClient=jack_client_new("GuitarSynth");
    if(mClient==0)
        this->errorMessage("Could not initialize Jack");

    if(jack_set_process_callback(mClient,GSEngine::process,0)!=0)
        this->errorMessage("Could not set Jack Process callback");

    mInput_port=jack_port_register (mClient, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    mOutput_port=jack_port_register (mClient, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    mMidiOut=jack_port_register(mClient,"midiout",JACK_DEFAULT_MIDI_TYPE,JackPortIsOutput,0);
    mSamplerate=jack_get_sample_rate(mClient);
    mBufferSize=jack_get_buffer_size(mClient);
    std::cout<<"Samplerate "<<mSamplerate<<" Buffersize "<<mBufferSize<<std::endl;


    mPitchDetector=new_aubio_pitch("yinfft",2*mBufferSize,mBufferSize,mSamplerate);
    //aubio_pitchdetection_set_yinthresh(mPitchDetector,1);
    mInputMag=0;
    mInBuf=new float[mBufferSize];
    mOutBuf=new float[mBufferSize];

}

void GSEngine::StartEngine()
{

    jack_activate(mClient);

}

void GSEngine::StopEngine()
{
    jack_deactivate(mClient);

}





void GSEngine::setInputGain(int val)
{
    mInputGain=((float)val/100.0f);


}

void GSEngine::setOutputGain(int val)
{
    mOutputGain=((float)val/100.0f);

}

void GSEngine::addSynth(SynthBase *synth)
{
    synth->setSamplerate(mSamplerate);
    synth->setBufferSize(mBufferSize);
    synth->InitBaseSynth();
    mSynths.push_back(synth);


}



void GSEngine::errorMessage(std::string err)
{
    QMessageBox msg;
    msg.setText(QString::fromStdString(err));
    msg.exec();
}

GSEngine * GSEngine::getInstance()
{
    if(mInstance=0)
        mInstance=new GSEngine();
}

int GSEngine::process(jack_nframes_t frames, void *arg)
{
    jack_default_audio_sample_t* in=(jack_default_audio_sample_t*)jack_port_get_buffer(mInstance->mInput_port,frames);
    jack_default_audio_sample_t* out=(jack_default_audio_sample_t*)jack_port_get_buffer(mInstance->mOutput_port,frames);

    mInstance->rectifyIn(frames,in);

//    for(int i=0;i<frames;i++)
//    {
//        (mInstance->mInBuf)[i]=(in[i]+fabs(in[i]))/2;
//    }
    fvec_t Buf;

    //Buf.channels=1;
    Buf.data=mInstance->mInBuf;
    Buf.length=frames;
    float freq;
    fvec_t* freqbuf=new_fvec(1);
    aubio_pitch_do(mInstance->mPitchDetector,&Buf,freqbuf);
    freq=freqbuf->data[0];
    del_fvec(freqbuf);
//    freq=(freq+mInstance->lastfreq)/2;
    freq=floor(freq);
    if(freq<0)
        freq=0;


    memset(out,0,frames*sizeof(jack_default_audio_sample_t));

    if(getMagnitude(frames,in)>1)
    {
        for(int i=0;i<mInstance->mSynths.size();i++)
            mInstance->mSynths[i]->process(frames,out,freq);
    }
//    memcpy(out,mInstance->mOutBuf,frames*sizeof(jack_default_audio_sample_t));
    mInstance->sendFrequence(freq);
//    mInstance->lastfreq=freq;
    return 0;
}

void GSEngine::sendFrequence(float val)
{
    emit freqChanged(val);
}

float GSEngine::getMagnitude(jack_nframes_t frames, float *buffer)
{
    float mag=0;
    for(int i=0;i<frames;i++)
        mag+=buffer[i]*buffer[i];
    mag=sqrt(mag);
    return mag;
}

void GSEngine::rectifyIn(int frames,float *in)
{
    for(int i=0;i<frames;i++)
    {
        mInBuf[i]=(in[i]+fabs(in[i]))/2;
    }
}


