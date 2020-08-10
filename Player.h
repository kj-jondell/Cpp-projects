#ifndef PLAYER_H
#define PLAYER_H

#include "Decoder.h"
#include "Sampler.h"
#include "portaudio.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>

#define IN_CHANNELS 1
#define OUT_CHANNELS 1
#define FRAMES_PER_BUFFER 512
#define SAMPLE_RATE 48000.f

#define INPUT_FEEDBACK 0.8f

#define RECORDING_CHAR '#'

using namespace std;

class Player {

private:
  int inputDeviceIndex = 0, outputDeviceIndex = 0;
  unsigned long timeKeeper = 0;
  PaError err;
  PaStream *stream;
  PaStreamParameters outputParameters, inputParameters;
  Decoder *decoder;
  Sampler *sampler;

  bool debug_, recordingMode;

  void initPlayer(const char *in, const char *out);
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
  Player(bool debug = false, const char *in = "", const char *out = "",
         const char *filePath = "");
  virtual ~Player();

  void start() { Pa_StartStream(stream); } // TODO implement error checking
  void stop() { Pa_CloseStream(stream); }  // TODO implement error checking
  void openStream();
};

#endif /* PLAYER_H */
