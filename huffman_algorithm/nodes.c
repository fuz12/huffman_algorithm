#include "nodes.h"

node* create_node() {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->frequency = 0;
    new_node->isSym = 0;
    new_node->symbol = 0;
    new_node->code[0] = '\0';
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

void swap(node** a, node** b) {
    node* temp = *b;
    *b = *a;
    *a = temp;
}

node* cpy_node(node* old_node) {
    node* new_node = (node*)malloc(sizeof(node));
    *new_node = *old_node;
    return new_node;
}

clean_node* create_clean_node() {
    clean_node* new_node = (clean_node*)malloc(sizeof(clean_node));
    new_node->isSym = 0;
    new_node->symbol = 0;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}