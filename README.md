# GuitarSynth
GuitarSynth is a set of wavetable synths controlled by a pitchdetector.
Actually it is not specific to guitars but can be used for any harmonic instrument.
This is a small petproject of mine to explore the possibilities of pitchdetection for Guitars.
It uses aubio for pitch detection, but that will change as I want to write my own detector.
Required:
Qt, Qt-dev,qmake
libjack, aubio

Compile:
I suggest an out-of-source build:
cd /parent/of/path/to/where-you-cloned-guitarsynth/
mkdir build
cd build
qmake ../GuitarSynth/GuitarSynth2.pro
make

That's it you should have am executable GuitarSynth2.
Start it, connect in qjackctl an audio source, turn up the gain on one the synths (beware with the square synth!!)
You mix the synths by turning up their individual gains.
Have fun

