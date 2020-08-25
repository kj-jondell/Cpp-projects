#ifndef DECODER_H
#define DECODER_H

#include "GoertzelFilter.hpp"
#include <iostream>
#include <map>
#include <vector>

#define MAX_LOSS 5

#define SEQUENCE_ENTRY_DELAY 15 // given in amt of buffers
#define AMT_CODES 7

using namespace std;

typedef struct ReceivedSymbol {
  char symbol;
  int notReceivedCounter; // TODO change name
  unsigned long receivedTime;
} ReceivedSymbol;

class Decoder {
private:
  const float DTMF_TABLE[2][4] = {{697.f, 770.f, 852.f, 941.f},
                                  {1209.f, 1336.f, 1477.f, NULL /*, 1633.f*/}};
  const char DECODE_TABLE[4][3] = {{'1', '2', '3'}, // 'A'},
                                   {'4', '5', '6'}, // 'B'},
                                   {'7', '8', '9'}, // 'C'},
                                   {'*', '0', '#'},
                                   /*'D'}*/};
  const map<char, int> SYMBOL_TO_INDEX = { // TODO better way to handle this!
      {'1', 0},  {'2', 1},  {'3', 2},  {'4', 3}, {'5', 4},  {'6', 5},
      {'7', 6},  {'8', 7},  {'9', 8},  {'*', 9}, {'0', 10}, {'#', 11},
      {'A', 12}, {'B', 13}, {'C', 14}, {1, 15},  {2, 16},   {3, 17},
      {4, 18},   {5, 19},   {6, 20},   {7, 21}};

  const string COMPARE_CODES[AMT_CODES] = {"1706", "2305", "4713", "19#2",
                                           "09*7", "1321", "560#"};

  float sampleRate_;
  ReceivedSymbol symbols[16];
  vector<ReceivedSymbol> currentSequence;

  float dbmThreshold;
  bool debug_;

  ReceivedSymbol *getSymbol(char ch);
  int getIndexOfSymbol(char ch);
  bool isPeak(float freq, float *in, int size);
  char parseSequence();

public:
  Decoder(float sampleRate, bool debug = false, float threshold = 0.0005);
  virtual ~Decoder();
  char getCode(float *in, int size, unsigned long time);
  int getIndexFromCode(char code);
};

#endif /* DECODER_H */
