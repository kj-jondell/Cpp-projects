#ifndef DECODER_H
#define DECODER_H

#include "GoertzelFilter.hpp"
#include <iostream>
#include <map>
#include <vector>

#define DBM_THRESHOLD 0.05
#define MAX_LOSS 5

using namespace std;

typedef struct ReceivedSymbol {
  char symbol;
  int notReceivedCounter; // TODO change name
} ReceivedSymbol;

class Decoder {
private:
  const float DTMF_TABLE[2][4] = {{697.f, 770.f, 852.f, 941.f},
                                  {1209.f, 1336.f, 1477.f, 1633.f}};
  const char DECODE_TABLE[4][4] = {{'1', '2', '3', 'A'},
                                   {'4', '5', '6', 'B'},
                                   {'7', '8', '9', 'C'},
                                   {'*', '0', '#', 'D'}};
  const map<char, int> SYMBOL_TO_INDEX = {
      {'1', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4},  {'6', 5},
      {'7', 6}, {'8', 7}, {'9', 8}, {'*', 9}, {'0', 10}, {'#', 11}};

  float sampleRate_;
  ReceivedSymbol symbols[16];

  bool debug_;

  ReceivedSymbol *getSymbol(char ch);
  int getIndexOfSymbol(char ch);
  bool isPeak(float freq, float *in, int size);

public:
  Decoder(float sampleRate, bool debug = false);
  virtual ~Decoder();
  char getCode(float *in, int size);
  int getIndexFromCode(char code);
};

#endif /* DECODER_H */
