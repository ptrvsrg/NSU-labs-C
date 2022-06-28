#include "output.h"

void OutputPathArray(int count, uint64_t* path)
{
    for (int i = 0; i < count; ++i)
    {
        if (path[i] == UINT64_MAX)
        {
            printf("oo ");
        }
        else if (path[i] > INT_MAX)
        {
            printf("INT_MAX+ ");
        }
        else
        {
            printf("%d ", (int)path[i]);
        }
    }
}

static int FindPreviousVertex(int vertexNum, uint64_t* pathArray, TGraph graph)
{
    for (int i = 0; i < graph.VertexCount; ++i)
    {
        int length = GetLengthGraph(vertexNum, i + 1, graph);
        if (length != 0 && pathArray[vertexNum - 1] == length + pathArray[i])
        {
            return i + 1;
        }
    }

    return 0;
}

static bool CheckOverflow(int vertexNum, int size, uint64_t* pathArray)
{
    if (pathArray[vertexNum - 1] <= INT_MAX)
    {
        return false;
    }

    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (i != vertexNum - 1 && pathArray[i] != UINT64_MAX && pathArray[i] >= INT_MAX)
        {
            ++count;
            if (count == 2)
            {
                return true;
            }
        }
    }

    return false;
}

void OutputShortestPath(int endVertex, uint64_t* pathArray, TGraph graph)
{
    if (pathArray[endVertex - 1] == UINT64_MAX)
    {
        printf("no path");
        return;
    }
    else if (CheckOverflow(endVertex, graph.VertexCount, pathArray))
    {
        printf("overflow");
        return;
    }

    printf("%d ", endVertex);

    while (pathArray[endVertex - 1] != 0)
    {
        endVertex = FindPreviousVertex(endVertex, pathArray, graph);
        if (endVertex == 0)
        {
            free(pathArray);
            DestroyGraph(&graph);
            OtherError(__FILE__, __LINE__);
        }

        printf("%d ", endVertex);
    }
}
