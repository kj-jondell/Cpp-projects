/**
 * A DTMF decoder and player for hacking an old phone (with RPi)
 *
 * TODO: - Implement error checking for portaudio
 * - Revise names (Player/Decoder)
 */

#include "Player.h"
#include "portaudio.h"
#include <iostream>

#define BREAK_CHAR '0'
#define DEBUG false

#define DEFAULT_INPUT_DEVICE_NAME "USB Audio Device: - (hw:2,0)"
#define DEFAULT_OUTPUT_DEVICE_NAME "USB Audio Device: - (hw:2,0)"
#define DEFAULT_REC_PATH                                                       \
  "/home/kj/Documents/projects/DTMFDecoder/Cpp-projects/recordings/"           \
  "Recording%d.wav"
#define DEFAULT_THRESHOLD 0.0005

#define DEFAULT_FILEPATH                                                       \
  "/home/kj/Documents/projects/DTMFDecoder/Cpp-projects/dtmf/sounds/"          \
  "Piano%d.wav"

using namespace std;

int main(int argc, char *argv[]) {
  // TODO better argument parsing (keys...)
  const char *in = argc >= 2 ? argv[1] : DEFAULT_INPUT_DEVICE_NAME,
             *out = argc >= 3 ? argv[2] : DEFAULT_OUTPUT_DEVICE_NAME,
             *filePath = argc >= 4 ? argv[3] : DEFAULT_FILEPATH,
             *recPath = argc >= 5 ? argv[4] : DEFAULT_OUTPUT_DEVICE_NAME;
  float threshold = argc >= 6 ? atof(argv[5]) : DEFAULT_THRESHOLD;
  bool debug = argc >= 7 ? (strcmp(argv[6], "debug") == 0) : DEBUG;

  Player *player = new Player(debug, in, out, filePath, recPath, threshold);

  player->openStream();
  player->start();

  while (getchar() != BREAK_CHAR)
    Pa_Sleep(50);

  player->stop();

  return 0;
}
