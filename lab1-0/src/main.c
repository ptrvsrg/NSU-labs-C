#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "boyer_moore.h"
#include "string.h"

int main(void)
{
    freopen("in.txt", "r", stdin);

    TString sample = CreateString();
    InputSample(&sample);
    BoyerMooreAlgorithm(sample);

    return EXIT_SUCCESS;
}
