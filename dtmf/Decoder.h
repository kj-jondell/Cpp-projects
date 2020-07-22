#ifndef DECODER_H
#define DECODER_H

#include "GoertzelFilter.hpp"
#include <iostream>
#include <vector>

#define DBM_THRESHOLD 0.00002
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
};

#endif /* DECODER_H */
