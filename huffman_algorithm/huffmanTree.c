//#include "huffmantree.h"
//
//node* huffmantree(priority_queue* q, int len) {
//
//    for (int i = 0; i < len - 1; i++) {
//        node* new_root = create_node();
//
//        node* first_child = extract_min(q);
//
//        node* second_child = extract_min(q);
//
//        new_root->issym = 0;
//
//        new_root->left = first_child;
//        new_root->right = second_child;
//
//        new_root->level++;
//
//        new_root->frequency = first_child->frequency + second_child->frequency;
//
//        insert(q, new_root);
//    }
//
//    return extract_min(q);
//}
//
////функция, в которой строим новый код для каждого символа из полученного алфавита *если сложно, начни ещё раз с прочтения*
//void trip(node* tree) {
//
//    if (tree == null) {
//        return;
//    }
//
//    priority_queue* q = create_pri_queue();
//    insert(q, tree);
//
//    //пока очередь не пустая, то извлекаем из очереди узел, левому в код записываем 0, а правому 1 *загляни в структуру я поменял немного её*
//    while (q->len > 0) {
//        node* temp = extract_min(q);
//
//        if (temp->left != null) {
//            insert(q, temp->left);
//            strcat(temp->left->code, temp->code);
//            strcat(temp->left->code, "0");
//        }
//
//        if (temp->right != null) {
//            insert(q, temp->right);
//            strcat(temp->right->code, temp->code);
//            strcat(temp->right->code, "1");
//        }
//
//        //если issym равен 1, то есть issym - байт, 0 - просто узел в дереве
//        if (temp->issym == 1) {
//            unsigned char sym = temp->symbol;
//            strcpy(abc[sym].code, temp->code);
//            abc[sym].sym = sym;
//            printf("%c %s\n", abc[sym].sym, abc[sym].code);
//            size++;
//        }
//    }
//}