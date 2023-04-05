#include <stdlib.h>
#include "priority_queue.h"

priority_queue* create_pri_queue() {
    priority_queue* pri_queue = (priority_queue*)malloc(sizeof(priority_queue));
    node* tmp = create_node();
    pri_queue->mas[0] = tmp;
    return pri_queue;
}

node* create_node() {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->frequency = 0;
    new_node->isSym = 0;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

void swap(node** a, node** b) {
    node* temp = *b;
    *b = *a;
    *a = temp;
}

void insert(priority_queue* pri_queue, node* new_node) {
    pri_queue->mas[0]->frequency += 1;
    int size = pri_queue->mas[0]->frequency;
    pri_queue->mas[size] = new_node;
    for (int i = size; i / 2 > 0; i /= 2) {
        if (pri_queue->mas[i]->frequency < pri_queue->mas[i / 2]->frequency) {
            swap(&pri_queue->mas[i], &pri_queue->mas[i / 2]);
        }
    }
}

node* Extract_min(priority_queue* pri_queue) {
    node* mine = cpy_node(pri_queue->mas[1]);
    int size = pri_queue->mas[0]->frequency;
    swap(&pri_queue->mas[size], &pri_queue->mas[1]);
    pri_queue->mas[size]->frequency = 0;
    --pri_queue->mas[0]->frequency;
    --size;
    int i = 1;
    while (i < size) {
        int r = i * 2;
        int l = i * 2 + 1;
        if (l <= size) {
            if (pri_queue->mas[l]->frequency <= pri_queue->mas[r]->frequency) {
                i = l;
            }
            if (pri_queue->mas[l]->frequency >= pri_queue->mas[r]->frequency) {
                i = r;
            }
        }
        else if (r <= size) {
            i = r;
        }
        else {
            break;
        }
        if (pri_queue->mas[i / 2]->frequency < pri_queue->mas[i]->frequency) {
            break;
        }
        swap(&pri_queue->mas[i], &pri_queue->mas[i / 2]);
    }
    return mine;
}

node* cpy_node(node* old_node) {
    node* new_node = (node*)malloc(sizeof(node));
    /*new_node->frequency = old_node->frequency;
    new_node->isSym = old_node->isSym;
    new_node->left = old_node->left;
    new_node->right = old_node->right;
    new_node->symbol = new_node->symbol;*/
    *new_node = *old_node;
    return new_node;
}

void free_queue(priority_queue* pri_queue) {
    free(pri_queue);
}