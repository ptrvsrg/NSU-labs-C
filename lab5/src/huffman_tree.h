#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <stdbool.h>
#include <stdlib.h>
#include "bitline.h"
#include "error.h"
#include "priority_list.h"
#include "stack.h"
#include "stream.h"
#include "tree.h"

TList CreateLeafList(TStream* stream);
TTree CreateHuffmanTree(TList* list);
void OutputHuffmanTree(TTree huffmanTree, TBitLine* bitLine, TStream* stream);
TTree InputHuffmanTree(TBitLine* bitLine, TStream* stream);

#endif
