#define _CRT_SECURE_NO_WARNINGS

#include <stddef.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "priority_queue.h"

node* huffmanTree(priority_queue* q, int len) {
    for (int i = 0; i < len - 1; i++) {
        node* new_root = create_node();
        node* first_child = Extract_min(q);
        printf("%d - ", first_child->frequency);
        node* second_child = Extract_min(q);        
        printf("%d - ", second_child->frequency);
        new_root->isSym = -1;
        new_root->left = first_child;
        new_root->right = second_child;
        new_root->frequency = first_child->frequency + second_child->frequency;
        printf("%d ", new_root->frequency);
        insert(q, new_root);
    }
    printf("\n");
    return Extract_min(q);
}

int main(void) { 
    int len = 6;
    priority_queue* Q = create_pri_queue();
    node* f = create_node();
    f->frequency = 5;
    node* e = create_node();
    e->frequency = 9;
    node* c = create_node();
    c->frequency = 12;
    node* b = create_node();
    b->frequency = 13;
    node* d = create_node();
    d->frequency = 16;
    node* a = create_node();
    a->frequency = 45;
    insert(Q, a);
    insert(Q, d);
    insert(Q, b);
    insert(Q, c);
    insert(Q, e);
    insert(Q, f);
    for (int i = 0; i < len; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", Q->mas[i]->frequency);
    }
    printf("\n");
    printf("\n");
    node* hTree = huffmanTree(Q, len);
    //printf("\n%d\n", Q->);
    printf("\n%d\n", hTree->frequency);
    for (int i = 0; i < len; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", Q->mas[i]->frequency);
    }
    printf("\n");    
    //node* bb = Extract_min(Q);
    //for (int i = 0; i < 4; i++) {
    //    printf("%d ", i);
    //}
    //printf("\n");
    //for (int i = 0; i < 4; i++) {
    //    printf("%d ", Q->mas[i]->frequency);
    //}   
    //printf("\n");
    //bb = Extract_min(Q);
    //for (int i = 0; i < 4; i++) {
    //    printf("%d ", i);
    //}
    //printf("\n");
    //for (int i = 0; i < 4; i++) {
    //    printf("%d ", Q->mas[i]->frequency);
    //}
    printf("\n");   
    free_queue(Q);
	return 0;
}