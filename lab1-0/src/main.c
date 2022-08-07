#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "boyer_moore.h"
#include "string.h"

int main(void)
{
    freopen("in.txt", "r", stdin);

    TString sample = CreateString();
    InputSample(MAX_LENGTH, &sample);
    BoyerMooreAlgorithm(sample);

    fclose(stdin);

    return EXIT_SUCCESS;
}
