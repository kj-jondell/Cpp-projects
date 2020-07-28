#include "Sampler.h"

Sampler::Sampler(const char *fileName) {
  char buf[100];
  for (int i = 1; i <= NUM_FILES; i++) {
    sprintf(buf, fileName, i);
    Sample newSample = {.file = SndfileHandle(buf)};
    samples.push_back(newSample);
  }
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
