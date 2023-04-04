#define _CRT_SECURE_NO_WARNINGS

#define MAX_SYM 256

#include <stddef.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
    char symbol;
    int frequency;
    struct node* left;
    struct node* right;
}node;

typedef struct priority_queue {
    node* mas[MAX_SYM]; // first element of mas is count of elements 
}priority_queue;

node* create_node() {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->frequency = 0;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

priority_queue* create_pri_queue() {
    priority_queue* pri_queue = (priority_queue*)malloc(sizeof(priority_queue));
    node* tmp = create_node();
    pri_queue->mas[0] = tmp;
    return pri_queue;
}

void swap(node* a, node* b) {
    node* temp = b;
    b = a;
    a = temp;
}

void insert(priority_queue* pri_queue, node* value) {    
    pri_queue->mas[0]->frequency += 1;
    int size = pri_queue->mas[0]->frequency;   
    pri_queue->mas[size] = value;    
    for (int i = size; i / 2 > 0; i /= 2) {        
        if (pri_queue->mas[i]->frequency < pri_queue->mas[i / 2]->frequency) {
            //swap(pri_queue->mas[i], pri_queue->mas[i / 2]);
            node* tmp = pri_queue->mas[i/2];
            pri_queue->mas[i / 2] = pri_queue->mas[i];
            pri_queue->mas[i] = tmp;           
        }
    }
}

node* Extract_min(priority_queue* pri_queue) {
    node mine = *pri_queue->mas[1];
    int size = pri_queue->mas[0]->frequency;
    //swap(pri_queue->mas[size], pri_queue->mas[1]);
    node* tmp = pri_queue->mas[size];
    pri_queue->mas[size] = pri_queue->mas[1];
    pri_queue->mas[1] = tmp;
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
        //swap(pri_queue->mas[i], pri_queue->mas[i / 2]);
        node* tmp = pri_queue->mas[i];
        pri_queue->mas[i] = pri_queue->mas[i / 2];
        pri_queue->mas[i / 2] = tmp;
    }
    return &mine;
}

node free_queue(priority_queue* pri_queue) {
    free(pri_queue);
}

int main(void) {
    srand(time(NULL));
    priority_queue* Q = create_pri_queue();
    node* a = create_node();
    a->frequency = 100;
    node* b = create_node();
    b->frequency = 50;
    node* c = create_node();
    c->frequency = 75;
    insert(Q, a);
    insert(Q, b);
    insert(Q, c);
    for (int i = 0; i < 4; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", Q->mas[i]->frequency);
    }
    printf("\n");    
    node* bb = Extract_min(Q);
    for (int i = 0; i < 4; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", Q->mas[i]->frequency);
    }   
    printf("\n");
    bb = Extract_min(Q);
    for (int i = 0; i < 4; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", Q->mas[i]->frequency);
    }
    printf("\n");   
    free_queue(Q);
	return 0;
}