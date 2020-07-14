#ifndef PLAYER_H
#define PLAYER_H

#include "portaudio.h"
#include <iostream>
#include <math.h>

#include "pa_mac_core.h"

#define DEVICE_NAME "Soundflower (64ch)"
#define IN_CHANNELS 1
#define OUT_CHANNELS 1
#define FRAMES_PER_BUFFER 64

#define M_PI (3.14159265)

using namespace std;

class Player {

private:
  int deviceIndex = 0;
  float sampleRate = 48000.f;

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
