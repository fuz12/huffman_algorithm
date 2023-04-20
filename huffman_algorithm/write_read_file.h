#pragma once

#include "defines.h"
#include "nodes.h"

void create_encoded_file(FILE* file_output, FILE* file, int countSym, node* tree, Alphabet* abc);

void create_decoded_file(FILE* file_outputRead, FILE* file_decoded);

void write_Huffman(node* avlleaf, FILE* f);

clean_node* read_Huffman(FILE* f);

void create_new_binstring(FILE* name, FILE* file_output, Alphabet* abc);

void init(unsigned char* arr);