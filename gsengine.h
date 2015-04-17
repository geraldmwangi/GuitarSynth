#ifndef GSENGINE_H
#define GSENGINE_H


#include <QObject>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <aubio/aubio.h>
#include <aubio/pitch/pitch.h>
#include <QList>


using namespace std;
class SynthBase;
class GSEngine: public QObject
{
    Q_OBJECT
public:
    static void errorMessage(string err);
    explicit GSEngine(QObject *parent=0);
    void InitNetwork();
    void StartEngine();
    void StopEngine();

    static int process(jack_nframes_t frames,void* arg);
    static float getMagnitude(jack_nframes_t frames,float* buffer);

    static GSEngine *getInstance();

    void sendFrequence(float val);


    void addSynth(SynthBase* synth);
    ~GSEngine();

    bool saveEngineNet(QString file);


    static GSEngine* mInstance;

signals:
    void freqChanged(float val);

public slots:
    void setInputGain(float val);
    void setOutputGain(float val);
private:

    float mInputGain;
    float mOutputGain;
    float mInputMag;
    QList<SynthBase*> mSynths;
    jack_nframes_t mSamplerate;
    jack_nframes_t mBufferSize;


    void rectifyIn(int frames,float* in);

    float* mInBuf;
    float* mOutBuf;
    jack_port_t *mInput_port;
    jack_port_t *mOutput_port;
    jack_port_t *mMidiOut;
    jack_client_t *mClient;
    aubio_pitch_t* mPitchDetector;
    float lastfreq;



};

#endif // GSENGINE_H
