#ifndef HASH_H
#define HASH_H

#include "string.h"

int Hash(int sampleLength, TString string);
int ChangeHash(unsigned char lastSymbol, unsigned char newSymbol, int powerOf3, int textHash);

#endif
