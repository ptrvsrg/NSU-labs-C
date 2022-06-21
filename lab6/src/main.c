#define _CRT_SECURE_NO_WARNINGS
#include "memory.h"
#include "avl-tree.h"

int main(void)
{
    int count = 0;
    if (scanf("%d", &count) == EOF)
    {
        return EXIT_FAILURE;
    }

    TMemory memory = CreateMemory(count, sizeof(TAVL));

    TAVLPtr tree = InputTree(count, &memory);
    printf("%d", GetHeight(tree));

    DestroyMemory(&memory);

    return EXIT_SUCCESS;
}
