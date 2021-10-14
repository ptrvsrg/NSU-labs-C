#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
	SUCCESS = 0,
	FAILURE = 1
};

struct TList
{
    int Value;
    struct TList* Next;
};

typedef struct TList* TList;

void InputList(size_t listSize, TList* list)
{
	if(listSize == 0)
    {
        (*list) = NULL;
    }
    else
    {
        TList new = malloc(sizeof(*new));
        assert(new != NULL);
        assert(scanf("%d", &(new->Value)) != EOF);
        (*list) = new;
        InputList(listSize - 1, &((*list)->Next));
    }
}

void OutputList(TList list)
{
    if(list != NULL)
    {
        printf("%d ", list->Value);
        OutputList(list->Next);
    }
}

void FreeList(TList* list) 
{
    if(*list != NULL)
    {
        FreeList(&((*list)->Next));
        free(*list);
    }
}

TList MergeLists(TList list1, TList list2)
{
    if(list1 == NULL)
    {
        return list2;
    }
    else if(list2 == NULL)
    {
        return list1;
    }
    else if(list1->Value < list2->Value)
    {
        list1->Next = MergeLists(list1->Next, list2);
        return list1;
    }
    else
    {
        list2->Next = MergeLists(list1, list2->Next);
        return list2;
    }
}

void SplitList(TList result, TList *low, TList *high) 
{
    TList fast = NULL;
    TList slow = NULL;
 
    if (result == NULL || result->Next == NULL)
    {
        (*low) = result;
        (*high) = NULL;
        return;
    }
 
    slow = result;
    fast = result->Next;
 
    while (fast != NULL) 
    {
        fast = fast->Next;
        if (fast != NULL) 
        {
            fast = fast->Next;
            slow = slow->Next;
        }
    }
 
    (*low) = result;
    (*high) = slow->Next;
    slow->Next = NULL;
}

void MergeSort(TList* list) 
{
    TList low  = NULL;
    TList high = NULL;

    if ((*list == NULL) || ((*list)->Next == NULL)) 
    {
        return;
    }

    SplitList(*list, &low, &high);
    MergeSort(&low);
    MergeSort(&high);
    (*list) = MergeLists(low, high);
}

int main()
{
	int listSize = 0;
    
	assert(scanf("%d", &listSize) != EOF);

	TList list;
	InputList(listSize, &list);
	MergeSort(&list);
	OutputList(list);
	FreeList(&list);
    
	return SUCCESS;
}
