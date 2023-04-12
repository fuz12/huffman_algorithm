#pragma once 

#include "defines.h"
#include "nodes.h"

typedef struct priority_queue {
    int len;
    node* mas[MAX_SYM]; // frequency field of first element is count of elements
}priority_queue;

priority_queue* create_pri_queue();

void insert(priority_queue* pri_queue, node* new_node);

node* Extract_min(priority_queue* pri_queue);

void free_queue(priority_queue* pri_queue);
