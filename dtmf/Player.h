#ifndef PLAYER_H
#define PLAYER_H

#include "Decoder.h"
#include "portaudio.h"
// #include "sndfile.hh"
#include <cstring>
#include <iostream>
#include <string>

#define INPUT_DEVICE_NAME "USB Audio Device: - (hw:2,0)"
#define OUTPUT_DEVICE_NAME "Scarlett 8i6 USB: Audio (hw:3,0)"
#define IN_CHANNELS 1
#define OUT_CHANNELS 1
#define FRAMES_PER_BUFFER 512
#define SAMPLE_RATE 48000.f

using namespace std;

class Player {

  private:
    int inputDeviceIndex = 0, outputDeviceIndex = 1;
    PaError err;
    PaStream *stream;
    PaStreamParameters outputParameters, inputParameters;
    Decoder *decoder;

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
    Player(bool debug = false);
    virtual ~Player();

    void start() { Pa_StartStream(stream); } // TODO implement error checking
    void stop() { Pa_CloseStream(stream); }  // TODO implement error checking
    void openStream();
};

#endif /* PLAYER_H */
