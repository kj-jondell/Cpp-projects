#ifndef SAMPLER_H
#define SAMPLER_H

#include "sndfile.hh"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>

#define FRAMES_PER_BUFFER 512
#define AMT_RECORDING_SLOTS 6
#define NUM_FILES 12
#define RECORDING_DURATION 1000 // frames ca. 10s

using namespace std;

typedef struct Sample {
  SndfileHandle file;
  bool playing = false, looping = false, recording = false;
  void togglePlaying() { playing = !playing; }
  void reset() { file.seek(0, 0); }
  void toggleRecording() { recording = !recording; }
} Sample;

class Sampler {

private:
  vector<Sample> samples;
  int recordingIndex = 0;
  unsigned long recordingTime = 0;

public:
  Sampler(const char *fileName);
  virtual ~Sampler();
  float *getNextFrame();
  void startRecording(int index, unsigned long time);
  bool recordFrame(float *in, unsigned long time);
  void stopAll() {
    for (int i = 0; i < samples.size(); i++) {
      samples[i].playing = false;
      if (samples[i].file)
        reset(i);
    }
  }
  void reset(int index) { samples[index].reset(); }
  void setPlaying(int index) {
    if (samples[index].looping)
      samples[index].togglePlaying();
    else
      samples[index].playing = true;
  }
};

#endif /* SAMPLER_H */
