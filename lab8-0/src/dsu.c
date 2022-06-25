#include "dsu.h"

TDSU CreateDSU(int vertexCount)
{
    TDSU dsu = { NULL, NULL };

    if (vertexCount > 0)
    {
        dsu.Parent = calloc(vertexCount, sizeof(*dsu.Parent));
        if (dsu.Parent == NULL)
        {
            OtherError(__FILE__, __LINE__);
        }

        for (int i = 0; i < vertexCount; ++i)
        {
            dsu.Parent[i] = i + 1;
        }

        dsu.Depth = calloc(vertexCount, sizeof(*dsu.Depth));
        if (dsu.Depth == NULL)
        {
            free(dsu.Parent);
            OtherError(__FILE__, __LINE__);
        }
    }

    return dsu;
}

int FindSet(int vertexNum, TDSU* dsu)
{
    if (dsu->Parent[vertexNum - 1] != vertexNum)
    {
        dsu->Parent[vertexNum - 1] = FindSet(dsu->Parent[vertexNum - 1], dsu);
    }

    return dsu->Parent[vertexNum - 1];
}

void MergeSet(int vertexNum1, int vertexNum2, TDSU* dsu)
{
    int set1 = FindSet(vertexNum1, dsu);
    int set2 = FindSet(vertexNum2, dsu);

    if (set1 == set2)
    {
        return;
    }

    if (dsu->Depth[set1 - 1] < dsu->Depth[set2 - 1])
    {
        dsu->Parent[set1 - 1] = set2;
    }
    else
    {
        dsu->Parent[set2 - 1] = set1;

        if (dsu->Depth[set1 - 1] == dsu->Depth[set2 - 1])
        {
            ++dsu->Depth[set1 - 1];
        }
    }
}

void DestroyDSU(TDSU* dsu)
{
    free(dsu->Parent);
    free(dsu->Depth);

    dsu->Parent = NULL;
    dsu->Depth = NULL;
}
