#include "Player.h"

Player::Player(bool debug) : debug_(debug) {
    initPlayer();
    sampler = new Sampler();
}

Player::~Player(void) { stop(); }

/**
 * Initilize Port audio
 */
void Player::initPlayer() {
    Pa_Initialize();

    for (int i = 0; i < Pa_GetDeviceCount(); i++) {
        // printf("%s\n", Pa_GetDeviceInfo(i)->name);
        // printf("%d\n", Pa_GetDeviceInfo(i)->maxOutputChannels);
        if (strcmp(Pa_GetDeviceInfo(i)->name, INPUT_DEVICE_NAME) == 0)
            inputDeviceIndex = i;
        if (strcmp(Pa_GetDeviceInfo(i)->name, OUTPUT_DEVICE_NAME) == 0)
            outputDeviceIndex = i;
    }

    // input settings
    inputParameters.channelCount = IN_CHANNELS;
    inputParameters.device = inputDeviceIndex;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency =
        Pa_GetDeviceInfo(inputDeviceIndex)->defaultLowInputLatency;

    // output settings
    outputParameters.channelCount = OUT_CHANNELS;
    outputParameters.device = outputDeviceIndex;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency =
        Pa_GetDeviceInfo(outputDeviceIndex)->defaultLowOutputLatency;
}

/**
 * Open port audio stream as definied in init
 */
void Player::openStream() {
    decoder = new Decoder(SAMPLE_RATE, debug_);
    err = Pa_OpenStream(&stream, &inputParameters, &outputParameters,
                        SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag,
                        staticPortAudioCallback, this);
}

/**
 * Port audio callback.
 * The input is analyzed with Goertzel or DFT/FFT to recognize DTMF.
 * Output according to decoded signal.
 */
int Player::portAudioCallback(const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo *timeInfo,
                              PaStreamCallbackFlags statusFlags) {
    float *in = (float *)inputBuffer, *out = (float *)outputBuffer;
    char code = decoder->getCode(in, framesPerBuffer);

    if (code) {
        int index = decoder->getIndexFromCode(code);
        sampler->reset(index);
        sampler->setPlaying(index);
    }

    float *nextFrame = sampler->getNextFrame();

    for (int i = 0; i < framesPerBuffer; i++)
        out[i] = 0.8 * nextFrame[i];

    if (debug_)
        if (code)
            printf("received: %c\n", code);
    ;
    // else ;// play soundfile    ;

    return paContinue;
}

/**
 * Static port audio callback.
 */
int Player::staticPortAudioCallback(const void *inputBuffer, void *outputBuffer,
                                    unsigned long framesPerBuffer,
                                    const PaStreamCallbackTimeInfo *timeInfo,
                                    PaStreamCallbackFlags statusFlags,
                                    void *userData) {
    return ((Player *)userData)
        ->portAudioCallback(inputBuffer, outputBuffer, framesPerBuffer,
                            timeInfo, statusFlags);
}
