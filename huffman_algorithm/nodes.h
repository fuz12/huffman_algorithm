#pragma once

#include "defines.h"

typedef struct node {
    unsigned char symbol;
    unsigned char isSym;
    int frequency;
    int level;
    char code[SIZE];
    struct node* left;
    struct node* right;
}node;

typedef struct clean_node {
    unsigned char symbol;
    char isSym;
    struct clean_node* right;
    struct clean_node* left;
} clean_node;

node* create_node();

node* cpy_node(node* old_node);

void swap(node** a, node** b);

clean_node* create_clean_node();