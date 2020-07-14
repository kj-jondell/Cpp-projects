#include "Player.h"

Player::Player() {
  Pa_Initialize();

  for (int i = 0; i < Pa_GetDeviceCount(); i++) {
    if (strcmp(Pa_GetDeviceInfo(i)->name, INPUT_DEVICE_NAME) == 0)
      inputDeviceIndex = i;
    if (strcmp(Pa_GetDeviceInfo(i)->name, OUTPUT_DEVICE_NAME) == 0)
      outputDeviceIndex = i;
  }

  inputParameters.channelCount = IN_CHANNELS;
  inputParameters.device = inputDeviceIndex;
  inputParameters.sampleFormat = paFloat32;
  inputParameters.suggestedLatency =
      Pa_GetDeviceInfo(inputDeviceIndex)->defaultLowInputLatency;

  outputParameters.channelCount = OUT_CHANNELS;
  outputParameters.device = outputDeviceIndex;
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(outputDeviceIndex)->defaultLowOutputLatency;

  err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, sampleRate,
                      FRAMES_PER_BUFFER, paNoFlag, portAudioCallback,
                      (void *)this);

  Pa_StartStream(stream);
  Pa_Sleep(5000);
  Pa_CloseStream(stream);
}

Player::~Player(void) {}

int Player::portAudioCallback(const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo *timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData) {

  float *in = (float *)inputBuffer, *out = (float *)outputBuffer, *sine;
  unsigned int i;
  (void)inputBuffer;

  for (i = 0; i < framesPerBuffer; i++)
    out[i] = in[i];

  return 0;
}
