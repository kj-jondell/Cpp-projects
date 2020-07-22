#ifndef SAMPLER_H
#define SAMPLER_H

#include "portaudio.h" // TODO remove dependency on portaudio
#include "sndfile.hh"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <vector>

#define FRAMES_PER_BUFFER 512
#define NUM_FILES 10

using namespace std;

typedef struct Sample {
    SndfileHandle file;
    bool playing = false, looping = false;
} Sample;

class Sampler {

  private:
    vector<Sample> samples;

  public:
    Sampler();
    virtual ~Sampler();
    float *getNextFrame();
};

#endif /* SAMPLER_H */
