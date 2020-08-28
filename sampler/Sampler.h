#ifndef SAMPLER_H
#define SAMPLER_H

#include "sndfile.hh"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <unistd.h>
#include <vector>

#define FRAMES_PER_BUFFER 512
#define AMT_RECORDING_SLOTS 7
#define NUM_FILES 15
#define IS_EXCLUSIVE -1
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
  const vector<vector<int>> NON_EXCLUSIVES = {
      {2, 4}, {6, 8}}; // indexes of non-exclusive groups i.e. samples that
                       // should be played together

  vector<Sample> samples;
  int recordingIndex = 0;
  unsigned long recordingTime = 0;

public:
  Sampler(const char *fileName, const char *recPath);
  virtual ~Sampler();
  float *getNextFrame();
  void startRecording(int index, unsigned long time);
  bool recordFrame(float *in, unsigned long time);
  void onlyPlayExclusive(int index) {
    int currentLayer = IS_EXCLUSIVE; // is exclusive
    for (int x = 0; x < NON_EXCLUSIVES.size(); x++)
      for (int y = 0; y < NON_EXCLUSIVES[x].size(); y++)
        if (NON_EXCLUSIVES[x][y] == index)
          currentLayer = x; // not exclusive and set layer

    if (samples[index].looping && currentLayer == IS_EXCLUSIVE)
      stopAllExcept(index);
    else if (currentLayer == IS_EXCLUSIVE) // is exclusive
      stopAll();
    else
      for (int i = 0; i < samples.size(); i++) {
        bool shouldPlay = false;
        if (samples[i].playing) {
          for (int y = 0; y < NON_EXCLUSIVES[currentLayer].size(); y++)
            if (i == NON_EXCLUSIVES[currentLayer][y]) {
              shouldPlay = true;
              break;
            }
          samples[i].playing = shouldPlay; // stop if not in non-exclusive layer
        }
      }
  }
  void stopRecordingMsg() {
    if (samples[11].playing)
      samples[11].playing = false;
    if (samples[12].playing)
      samples[12].playing = false;
  }
  void stopAllExcept(int index) {
    for (int i = 0; i < samples.size(); i++)
      if (i != index) {
        samples[i].playing = false;
        if (samples[i].file)
          reset(i);
      }
  }
  void stopAll() { stopAllExcept(-1); } // no exceptions
  void reset(int index) { samples[index].reset(); }
  void setPlaying(int index) {
    if (samples[index].looping)
      samples[index].togglePlaying();
    else
      samples[index].playing = true;
  }
};

#endif /* SAMPLER_H */
