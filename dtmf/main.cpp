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
#define DEBUG true

using namespace std;

int main(int argc, char *argv[]) {

  Player *player = new Player(DEBUG);

  player->openStream();
  player->start();

  while (getchar() != BREAK_CHAR)
    Pa_Sleep(50);

  player->stop();

  return 0;
}
