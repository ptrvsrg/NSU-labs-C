#ifndef ENCODE_H
#define ENCODE_H

#include <stdbool.h>
#include <stdlib.h>
#include "bitline.h"
#include "code_table.h"
#include "error.h"
#include "huffman_tree.h"
#include "stream.h"
#include "tree.h"

void Encode(TStream stream);

#endif
