#ifndef HASH_H
#define HASH_H

#include "circular_list.h"

int Hash(TCircularList list);
int ChangeHash(unsigned char lastSymbol, unsigned char newSymbol, int powerOf3, int textHash);

#endif
