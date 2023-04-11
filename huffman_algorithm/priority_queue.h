#ifndef HUFFMAN_ALGORITHM_PRIORITY_QUEUE_H
#define HUFFMAN_ALGORITHM_PRIORITY_QUEUE_H
#pragma once

#define MAX_SYM 257
#define SIZE 257

typedef struct node {
    unsigned char symbol;
    unsigned char isSym;
    int frequency;    
    int level;
    char code[SIZE];
    struct node* left;
    struct node* right;
}node;

typedef struct priority_queue {
    int len;
    node* mas[MAX_SYM]; // frequency field of first element is count of elements
}priority_queue;

priority_queue* create_pri_queue();

node* create_node();

void swap(node** a, node** b);

void insert(priority_queue* pri_queue, node* new_node);

node* Extract_min(priority_queue* pri_queue);

node* cpy_node(node* old_node);

void free_queue(priority_queue* pri_queue);
#endif //HUFFMAN_ALGORITHM_PRIORITY_QUEUE_H
