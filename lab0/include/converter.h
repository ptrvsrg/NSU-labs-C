#ifndef CONVERTER_H
#define CONVERTER_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

char* ConvertNumber(int systemBase1, int systemBase2, const char* number, int digitAfterPoint);

#endif
