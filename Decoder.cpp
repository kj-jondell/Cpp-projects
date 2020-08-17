#include "Decoder.h"

Decoder::Decoder(float sampleRate, bool debug, float treshold)
    : sampleRate_(sampleRate), debug_(debug), dbmThreshold(treshold) {
  for (int i = 0; i < 16; i++) {
    symbols[i].symbol = DECODE_TABLE[i / 4][i % 4];
    symbols[i].notReceivedCounter = MAX_LOSS;
  }
}
Decoder::~Decoder(void) {}

bool Decoder::isPeak(float freq, float *in, int size) {
  float goertzelPeak =
      GoertzelFilter<float>(freq, sampleRate_).process(in, size);
  //      if(goertzelPeak > dbmThreshold && debug_)
  //        printf("peak for %f is %f\n", freq, goertzelPeak);
  return goertzelPeak > dbmThreshold;
}

/**
 * Returns object of given symbol. TODO implement when checking for falling
 * edges. Maybe use timer?
 */
ReceivedSymbol *Decoder::getSymbol(char ch) {
  for (auto returnSymbol : symbols)
    if (returnSymbol.symbol == ch)
      return &returnSymbol;
}

int Decoder::getIndexOfSymbol(char ch) {
  for (int i = 0; i < 16; i++)
    if (symbols[i].symbol == ch)
      return i;
}

int Decoder::getIndexFromCode(char code) { return SYMBOL_TO_INDEX.at(code); }

/**
 * Parse phone number (number sequence) and return code if number does not have
 * special action!
 */
char Decoder::parseSequence() {
  string sequence;
  for (int i = 0; i < currentSequence.size(); i++)
    sequence.push_back(currentSequence.at(i).symbol);

  for (int i = 0; i < AMT_CODES; i++)
    if (!sequence.compare(COMPARE_CODES[i]))
      return (char)(i + 1);

  return currentSequence.back().symbol; // return last pressed digit
}

/**
 * Checking for falling edges TODO boolean to get on rising/falling edge?
 */
char Decoder::getCode(float *in, int size, unsigned long time) {
  char returnedChar = NULL;
  int receivedIndex = -1;

  for (int x = 0; x < 4; x++)
    for (int y = 0; y < 3; y++) {
      int index = getIndexOfSymbol(DECODE_TABLE[x][y]);
      bool receivedOne = isPeak(DTMF_TABLE[0][x], in, size),
           receivedTwo = isPeak(DTMF_TABLE[1][y], in, size);

      if (receivedOne && receivedTwo) {
        if (symbols[index].notReceivedCounter >= MAX_LOSS) {
          symbols[index].notReceivedCounter = 0;
        }
      } else if (symbols[index].notReceivedCounter < MAX_LOSS)
        if (++symbols[index].notReceivedCounter == MAX_LOSS) {
          receivedIndex = index;
          symbols[index].receivedTime = time;
        }
    }

  if (receivedIndex >= 0) {
    currentSequence.push_back(symbols[receivedIndex]);
  }

  if (currentSequence.size() > 0)
    if ((time - currentSequence.back().receivedTime) > SEQUENCE_ENTRY_DELAY) {
      returnedChar = parseSequence(); // signal on falling edge!
      currentSequence.clear();
    }

  return returnedChar;
}
