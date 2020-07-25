#include "Sampler.h"

Sampler::Sampler() {
  char buf[50];
  for (int i = 1; i <= NUM_FILES; i++) {
    sprintf(buf, "../sounds/Slice%d.wav", i);
    Sample newSample = {.file = SndfileHandle(buf)};
    samples.push_back(newSample);
  }
  samples[3].looping = true;
  samples[7].looping = true;
  samples[9].looping = true;
}
Sampler::~Sampler(void) {}

float *Sampler::getNextFrame() {
  static float summedBuffer[FRAMES_PER_BUFFER];
  memset(summedBuffer, 0.f, sizeof summedBuffer);

  for (int i = 0; i < NUM_FILES; i++) {
    if (samples[i].playing) {
      static float buffer[FRAMES_PER_BUFFER];
      if (!samples[i].file.read(buffer, FRAMES_PER_BUFFER)) {
        if (!samples[i].looping)
          samples[i].playing = false;
        reset(i);
      }
      for (int index = 0; index < FRAMES_PER_BUFFER; index++)
        summedBuffer[index] += buffer[index];
    }
  }
  return summedBuffer;
}
