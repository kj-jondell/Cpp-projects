#ifndef PLAYER_H
#define PLAYER_H

#include "portaudio.h"
#include <iostream>

#define INPUT_DEVICE_NAME "Soundflower (64ch)"
#define OUTPUT_DEVICE_NAME "Built-in Output"
#define IN_CHANNELS 1
#define OUT_CHANNELS 1
#define FRAMES_PER_BUFFER 512

using namespace std;

class Player {

private:
  int inputDeviceIndex = 0, outputDeviceIndex = 1;
  float sampleRate = 48000.f;
  PaError err;
  PaStream *stream;
  PaStreamParameters outputParameters, inputParameters;

  static int portAudioCallback(const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo *timeInfo,
                               PaStreamCallbackFlags statusFlags,
                               void *userData);

public:
  Player();
  virtual ~Player();
};

#endif /* PLAYER_H */
