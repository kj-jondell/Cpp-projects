#include "Decoder.h"

Decoder::Decoder(float sampleRate, bool debug)
    : sampleRate_(sampleRate), debug_(debug) {
  for (int i = 0; i < 16; i++) {
    symbols[i].symbol = DECODE_TABLE[i / 4][i % 4];
    symbols[i].notReceivedCounter = MAX_LOSS;
  }
}
Decoder::~Decoder(void) {}

bool Decoder::isPeak(float freq, float *in, int size) {
  return GoertzelFilter<float>(freq, sampleRate_).process(in, size) >
         DBM_THRESHOLD;
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

  if (!sequence.compare("1706")) { // different "cases"
    if (debug_)
      cout << "record 1!" << endl;
    return NULL;
  } else if (!sequence.compare("2305")) { // different "cases"
    if (debug_)
      cout << "record 2!" << endl;
    return NULL;
  } else if (!sequence.compare("4713")) { // different "cases"
    if (debug_)
      cout << "record 3!" << endl;
    return NULL;
  } else if (!sequence.compare("19#2")) { // different "cases"
    if (debug_)
      cout << "record 4!" << endl;
    return NULL;
  } else if (!sequence.compare("09*7")) { // different "cases"
    if (debug_)
      cout << "record 5!" << endl;
    return NULL;
  } else if (!sequence.compare("1321")) { // different "cases"
    if (debug_)
      cout << "record 6!" << endl;
    return NULL;
  } else
    return currentSequence.back().symbol; // return last pressed digit
}

/** 2
 * Checking for falling edges TODO boolean to get on rising/falling edge?
 */
char Decoder::getCode(float *in, int size, unsigned long time) {
  char returnedChar = NULL;
  for (int x = 0; x < 4; x++)
    for (int y = 0; y < 3; y++) {
      int index = getIndexOfSymbol(DECODE_TABLE[x][y]);

      if (isPeak(DTMF_TABLE[0][x], in, size) &&
          isPeak(DTMF_TABLE[1][y], in, size)) {
        if (symbols[index].notReceivedCounter >= MAX_LOSS) {
          symbols[index].notReceivedCounter = 0;
        }
      } else if (symbols[index].notReceivedCounter < MAX_LOSS)
        if (++symbols[index].notReceivedCounter == MAX_LOSS &&
            returnedChar == NULL) {
          symbols[index].receivedTime = time;
          currentSequence.push_back(symbols[index]);
        }
    }

  if (currentSequence.size() > 0)
    if ((time - currentSequence.back().receivedTime) > SEQUENCE_ENTRY_DELAY) {
      returnedChar = parseSequence(); // signal on falling edge!
      currentSequence.clear();
    }

  return returnedChar;
}
