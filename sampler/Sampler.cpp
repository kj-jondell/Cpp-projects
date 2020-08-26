#include "Sampler.h"

Sampler::Sampler(const char *fileName, const char *recordingFileName) {
  char buf[100];
  for (int i = 1; i <= NUM_FILES; i++) {
    sprintf(buf, fileName, i);
    Sample newSample = {.file = SndfileHandle(buf)};
    samples.push_back(newSample);
  }
  for (int i = 1; i <= AMT_RECORDING_SLOTS; i++) {
    sprintf(buf,
            recordingFileName, // TODO make variable
            i);

    Sample newSample = {
        .file = SndfileHandle(buf, SFM_RDWR, SF_FORMAT_WAV | SF_FORMAT_PCM_16,
                              1, 48000)}; // TODO variable samplerate
    samples.push_back(newSample);
  }
  samples[2].looping = true;
  samples[4].looping = true;
  samples[6].looping = true;

  samples[2].exclusive = false;
  samples[4].exclusive = false;
  samples[6].exclusive = false;
}
Sampler::~Sampler(void) {}

/**
 * Return next frame of audio.
 */
float *Sampler::getNextFrame() {
  static float summedBuffer[FRAMES_PER_BUFFER];
  memset(summedBuffer, 0.f, sizeof summedBuffer);

  for (int i = 0; i < samples.size(); i++) {
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

/**
 * Initilize recording
 */
void Sampler::startRecording(int index, unsigned long recordingTime) {
  this->recordingTime = recordingTime;
  recordingIndex = index - 1;

  stopAll();
}

/**
 * Writes buffer of recording
 * Returns true if still recording
 */
bool Sampler::recordFrame(float *in, unsigned long time) {
  if (time < (recordingTime + RECORDING_DURATION)) {
    for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
      in[i] *= 8.f;    // gain
      if (in[i] > 1.f) // limiter
        in[i] = 1.f;
      else if (in[i] < -1.f)
        in[i] = -1.f;
    }
    samples[NUM_FILES + recordingIndex].file.writef(in, FRAMES_PER_BUFFER);
    return true;
  } else {
    samples[NUM_FILES + recordingIndex].file.command(
        SFC_UPDATE_HEADER_NOW, NULL, 0); // necessary to write file correctly
    samples[NUM_FILES + recordingIndex].file.writeSync();
    return false;
  }
}
