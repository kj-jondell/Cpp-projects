#include "Player.h"

Player::Player() {
  Pa_Initialize();

  for (int i = 0; i < Pa_GetDeviceCount(); i++)
    if (strcmp(Pa_GetDeviceInfo(i)->name, DEVICE_NAME) == 0)
      deviceIndex = i;

  PaStream *stream;
  PaStreamParameters outputParameters;
  PaStreamParameters inputParameters;

  bzero(&inputParameters, sizeof(inputParameters));
  inputParameters.channelCount = IN_CHANNELS;
  inputParameters.device = deviceIndex;
  inputParameters.hostApiSpecificStreamInfo = NULL;
  inputParameters.sampleFormat = paFloat32;
  inputParameters.suggestedLatency =
      Pa_GetDeviceInfo(deviceIndex)->defaultLowInputLatency;

  bzero(&outputParameters, sizeof(outputParameters));
  outputParameters.channelCount = OUT_CHANNELS;
  outputParameters.device = deviceIndex;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(deviceIndex)->defaultLowOutputLatency;

  sampleRate = Pa_GetDeviceInfo(deviceIndex)->defaultSampleRate;

  int err = Pa_OpenStream(&stream, &inputParameters, &outputParameters,
                          sampleRate, FRAMES_PER_BUFFER, paNoFlag,
                          portAudioCallback, (void *)this);

  Pa_StartStream(stream);
  Pa_Sleep(1000);
  Pa_CloseStream(stream);
}

Player::~Player(void) {}

int Player::portAudioCallback(const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo *timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData) {

  float *out = (float *)outputBuffer;
  unsigned int i;
  (void)inputBuffer;

  for (i = 0; i < framesPerBuffer; i++)
    out[i] = (float)sin(((double)i / (double)framesPerBuffer) * M_PI * 2.);

  return 0;
}
