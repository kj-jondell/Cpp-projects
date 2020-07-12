#ifndef DECODER_H
#define DECODER_H

#include <iostream>

using namespace std;

class Decoder {
  private:
    float goertzel();

  public:
    Decoder();
    virtual ~Decoder();
};

#endif /* DECODER_H */
