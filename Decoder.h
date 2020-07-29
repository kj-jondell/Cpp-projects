#ifndef DECODER_H
#define DECODER_H

#include "GoertzelFilter.hpp"
#include <iostream>
#include <map>
#include <vector>

#define DBM_THRESHOLD 0.0005
#define MAX_LOSS 5

#define SEQUENCE_ENTRY_DELAY 15 // given in amt of buffers

using namespace std;

typedef struct ReceivedSymbol {
    char symbol;
    int notReceivedCounter; // TODO change name
    unsigned long receivedTime;
} ReceivedSymbol;

class Decoder {
  private:
    const float DTMF_TABLE[2][4] = {
        {697.f, 770.f, 852.f, 941.f},
        {1209.f, 1336.f, 1477.f, NULL /*, 1633.f*/}};
    const char DECODE_TABLE[4][3] = {{'1', '2', '3'}, // 'A'},
                                     {'4', '5', '6'}, // 'B'},
                                     {'7', '8', '9'}, // 'C'},
                                     {'*', '0', '#'},
                                     /*'D'}*/};
    const map<char, int> SYMBOL_TO_INDEX = { // TODO better way to handle this!
        {'1', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4},  {'6', 5},
        {'7', 6}, {'8', 7}, {'9', 8}, {'*', 9}, {'0', 10}, {'#', 11}};

    float sampleRate_;
    ReceivedSymbol symbols[16];
    vector<ReceivedSymbol> currentSequence;

    bool debug_;

    ReceivedSymbol *getSymbol(char ch);
    int getIndexOfSymbol(char ch);
    bool isPeak(float freq, float *in, int size);
    char parseSequence();

  public:
    Decoder(float sampleRate, bool debug = false);
    virtual ~Decoder();
    char getCode(float *in, int size, unsigned long time);
    int getIndexFromCode(char code);
};

#endif /* DECODER_H */
