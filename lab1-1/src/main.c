#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "rabin_karp.h"

int main(void)
{
    TString sample = CreateString();
    InputSample(&sample);
    RabinKarpAlgorithm(sample);

    return EXIT_SUCCESS;
}
