#define _CRT_SECURE_NO_WARNINGS

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <Windows.h>
#include "priority_queue.h"
#define BIT8 8
#define LEN 1000000000

typedef struct alphabet{
    char code[SIZE]; // новый бинарный код байта
    unsigned char sym; // сам байт
} Alphabet;

//храним коды файла
int size = 0; // кол-во уникальных значений
Alphabet abc[SIZE];

//новая бинарная строка
char string[LEN];
//тут есть проблема, так как файл может быть большого размера, то такого способа хранения хватит не на много, !ВАЖНО!
//поэтому нужно придумать как записывать строку в бинарный файл !ВАЖНО!

typedef union bit2char{
    unsigned char symb;
    struct bit{
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
    } mbit;
} BIT2CHAR;

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

//функция, в которой строим новый код для каждого символа из полученного алфавита *если сложно, начни ещё раз с прочтения*
void trip(node* tree){

    if(tree == NULL){
        return;
    }

    priority_queue* q = create_pri_queue();
    insert(q, tree);

    //пока очередь не пустая, то извлекаем из очереди узел, левому в код записываем 0, а правому 1 *загляни в структуру я поменял немного её*
    while(q->len > 0){
        node* temp = Extract_min(q);

        if(temp -> left != NULL){
            insert(q, temp->left);
            strcat(temp->left->code, temp->code);
            strcat(temp->left->code, "0");
        }

        if(temp -> right != NULL){
            insert(q, temp->right);
            strcat(temp->right->code, temp->code);
            strcat(temp->right->code, "1");
        }

        //если isSym равен 1, то есть isSym - байт, 0 - просто узел в дереве
        if(temp -> isSym == 1){
            unsigned char sym = temp->symbol;
            strcpy(abc[sym].code,temp->code);
            abc[sym].sym = sym;
            printf("%c %s\n", abc[sym].sym, abc[sym].code);
            size++;
        }
    }
}

void create_new_binstring(FILE *name, char* binstring){
    unsigned char c; // переменная для записи прочитанного байта
    //читаем файл по байту и находим в массиве abc такой же байт и копируем его новый код в бинарную строку
    long long int ind = 0;
    while(fread(&c, sizeof(unsigned char), 1, name)){
        for (int i = 0; abc[c].code[i] != '\0'; i++) {
            string[ind++] = abc[c].code[i];
        }
    }
    fseek(name, 0, SEEK_SET);
    //printf("Binary: %s\n", string);  //можешь посмотреть полученную строку
};

int main(void) {
    
    SetConsoleCP(1251);       
    SetConsoleOutputCP(1251);

    priority_queue* Q = create_pri_queue(); // создаём очередь с приоритетом

    int len = 0; // кол-во использованных букв в файле (алфавит) 

    long long int countSym = 0;

    int freq[SIZE] = {0}; // частотный словарь

    //открываем входной и выходной файлы
    FILE *file = fopen("tests/inputbmp.bmp", "rb");
    FILE *file_output = fopen("tests/outputbmp.bmp", "wb");
    FILE* file_decoded = fopen("tests/decodedbmp.bmp", "wb");


    //обрабатываем ошибку не существующего файла
    if(file == NULL){
        printf("Error input");
        exit(EXIT_FAILURE);
    }

    unsigned char ch; // переменная для записи прочитанного байта

    //читаем файл и создаём частотный словарь
    while(fread(&ch, sizeof(unsigned char), 1, file)){
        freq[ch]++;
        countSym++;
    }
    fseek(file, 0, SEEK_SET); // после прочтения файл переводим указатель в начало файла

    //заполняем очередь с приоритетом, используя только что частотный словарь
    for(int i = 0; i < SIZE; i++){
        if(freq[i] > 0){
            node* temp = create_node();
            temp -> frequency = freq[i];
            temp -> symbol = i;
            temp -> isSym = 1;            
            insert(Q, temp);
            len++;
        }
    }

    char* binstring = (char*)malloc(countSym * sizeof(char));

    node* tree = huffmanTree(Q, len); // создали дерево
    node* tree_for_trip = cpy_node(tree);
    trip(tree_for_trip); //нашли коды для записи каждого байта и сохранили в abc
    create_new_binstring(file, binstring); // создаём строчку с новым бинарным кодом текущего файла

    long count = strlen(string) / BIT8; // целое кол-во байт в новой строке с бинарным кодом

    if (file_output == NULL) {
        printf("Error output");
        exit(EXIT_FAILURE);
    }
    BIT2CHAR symb;
    for(int i = 0; i < count + 1; i++){
        symb.mbit.b1 = string[i*BIT8 + 7];
        symb.mbit.b2 = string[i*BIT8 + 6];
        symb.mbit.b3 = string[i*BIT8 + 5];
        symb.mbit.b4 = string[i*BIT8 + 4];
        symb.mbit.b5 = string[i*BIT8 + 3];
        symb.mbit.b6 = string[i*BIT8 + 2];
        symb.mbit.b7 = string[i*BIT8 + 1];
        symb.mbit.b8 = string[i*BIT8 + 0];
        putc(symb.symb, file_output);
    }
    fseek(file_output, 0, SEEK_SET);      

    FILE* file_kkk = fopen("tests/outputbmp.bmp", "rb");
    if (file_decoded == NULL) {
        printf("Error decoded");
        exit(EXIT_FAILURE);
    }
    char byte[8];   
    node* root = tree;   
    printf("\n");
    while (fread(&symb.symb, sizeof(unsigned char), 1, file_kkk)) {
        byte[0] = symb.mbit.b1;
        byte[1] = symb.mbit.b2;
        byte[2] = symb.mbit.b3;
        byte[3] = symb.mbit.b4;
        byte[4] = symb.mbit.b5;
        byte[5] = symb.mbit.b6;
        byte[6] = symb.mbit.b7;
        byte[7] = symb.mbit.b8;
        for (int i = BIT8 - 1; i >= 0 && countSym != 0; i--) {       
            if (tree->isSym == 1) {
                putc(tree->symbol, file_decoded);
                tree = root;
                countSym--;
            }
            if (byte[i] == 0) {                
                tree = tree->left;
            }
            else {
                tree = tree->right;
            }     
        }
    }

    free_queue(Q);
    fclose(file);
    fclose(file_output);
    fclose(file_decoded);
    return 0;
}