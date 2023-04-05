#pragma once

#define MAX_SYM 256

typedef struct node {
    char symbol;
    char isSym; // 0 if symbol, -1 if not
    int frequency;
    struct node* left;
    struct node* right;
}node;

typedef struct priority_queue {
    node* mas[MAX_SYM]; // frequency field of first element is count of elements 
}priority_queue;

priority_queue* create_pri_queue();

node* create_node();

void swap(node** a, node** b);

void insert(priority_queue* pri_queue, node* new_node);

node* Extract_min(priority_queue* pri_queue);

node* cpy_node(node* old_node);

void free_queue(priority_queue* pri_queue);