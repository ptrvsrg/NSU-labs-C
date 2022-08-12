#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "knuth_morris_pratt.h"
#include "prefix_function.h"
#include "string.h"

int main(void)
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    TString sample = CreateString();
    InputSample(&sample);
    KMPAlgorithm(sample);

    fclose(stdin);
    fclose(stdout);

    return EXIT_SUCCESS;
}
