#include "huffmanTree.h"

node* huffmanTree(priority_queue* q, int len) {

    for (int i = 0; i < len - 1; i++) {
        node* new_root = create_node();

        node* first_child = Extract_min(q);

        node* second_child = Extract_min(q);

        new_root->isSym = 0;

        new_root->left = first_child;
        new_root->right = second_child;

        new_root->level++;

        new_root->frequency = first_child->frequency + second_child->frequency;

        insert(q, new_root);
    }

    return Extract_min(q);
}

void trip(node* tree, Alphabet* abc, int size) {

    if (tree == NULL) {
        return;
    }

    priority_queue* q = create_pri_queue();
    insert(q, tree);

    // Пока очередь не пустая, то извлекаем из очереди узел, левому в код записываем 0, а правому 1
    while (q->len > 0) {
        node* temp = Extract_min(q);

        if (temp->left != NULL) {
            insert(q, temp->left);
            strcat(temp->left->code, temp->code);
            strcat(temp->left->code, "0");
        }

        if (temp->right != NULL) {
            insert(q, temp->right);
            strcat(temp->right->code, temp->code);
            strcat(temp->right->code, "1");
        }

        // Если isSym равен 1, то isSym - символ, 0 - просто узел в дереве
        if (temp->isSym == 1) {
            unsigned char sym = temp->symbol;
            strcpy(abc[sym].code, temp->code);
            abc[sym].sym = sym;
            size++;
        }
    }
}