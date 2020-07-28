#ifndef SAMPLER_H
#define SAMPLER_H

#include "sndfile.hh"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <vector>

#define FRAMES_PER_BUFFER 512
#define NUM_FILES 12

using namespace std;

typedef struct Sample {
  SndfileHandle file;
  bool playing = false, looping = false;
  void togglePlaying() { playing = !playing; }
  void reset() { file.seek(0, 0); }
} Sample;

class Sampler {

private:
  vector<Sample> samples;

public:
  Sampler(const char *fileName);
  virtual ~Sampler();
  float *getNextFrame();
  void reset(int index) { samples[index].reset(); }
  void setPlaying(int index) {
    if (samples[index].looping)
      samples[index].togglePlaying();
    else
      samples[index].playing = true;
  }
};

#endif /* SAMPLER_H */
