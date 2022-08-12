#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "knuth_morris_pratt.h"
#include "prefix_function.h"
#include "string.h"

int main(void)
{
    TString sample = CreateString();
    InputSample(&sample);
    KMPAlgorithm(sample);

    return EXIT_SUCCESS;
}
