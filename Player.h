#ifndef PLAYER_H
#define PLAYER_H

#include "Decoder.h"
#include "Sampler.h"
#include "portaudio.h"
#include <cstring>
#include <iostream>
#include <string>

#define IN_CHANNELS 1
#define OUT_CHANNELS 1
#define FRAMES_PER_BUFFER 512
#define SAMPLE_RATE 48000.f

using namespace std;

class Player {

private:
  int inputDeviceIndex = 0, outputDeviceIndex = 1;
  char *inputDeviceName_, *outputDeviceName_;
  PaError err;
  PaStream *stream;
  PaStreamParameters outputParameters, inputParameters;
  Decoder *decoder;
  Sampler *sampler;

  bool debug_;

  void initPlayer();
  int portAudioCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags);
  static int staticPortAudioCallback(const void *inputBuffer,
                                     void *outputBuffer,
                                     unsigned long framesPerBuffer,
                                     const PaStreamCallbackTimeInfo *timeInfo,
                                     PaStreamCallbackFlags statusFlags,
                                     void *userData);

public:
  Player(bool debug = false, char *in = "USB Audio Device: - (hw:2,0)",
         char *out = "USB Audio Device: - (hw:2,0)");
  virtual ~Player();

  void start() { Pa_StartStream(stream); } // TODO implement error checking
  void stop() { Pa_CloseStream(stream); }  // TODO implement error checking
  void openStream();
};

#endif /* PLAYER_H */
