#pragma once // ������ / ������ ������ �������� � ������ �����

#include "defines.h"
#include "nodes.h"

void write(node* avlleaf, FILE* f);

clean_node* read(FILE* f);
