#ifndef STREAM_H
#define STREAM_H

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

typedef struct TStream
{
    FILE* In;
    FILE* Out;
} TStream;

TStream CreateStream(void);
int InputStream(void* value, int size, int count, TStream stream);
void OutputStream(void* value, int size, int count, TStream stream);
void DestroyStream(TStream* stream);

#endif
