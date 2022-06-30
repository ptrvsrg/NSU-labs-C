#include "circular_list.h"
#include "rabin_karp.h"
#define SIZE_TEMPLATE (int)16

int main(void)
{
    TCircularList template = CreateCircularList(SIZE_TEMPLATE);
    InputTemplate(SIZE_TEMPLATE, &template);
    RabinKarpAlgorithm(template);
    DestroyCircularList(&template);

    return EXIT_SUCCESS;
}
