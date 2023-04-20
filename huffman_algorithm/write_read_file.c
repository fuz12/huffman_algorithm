#include "write_read_file.h"

void create_encoded_file(FILE* file_output, FILE* file, int countSym, node* tree, Alphabet* abc) {
    fwrite(&countSym, sizeof(int), 1, file_output);
    write_Huffman(tree, file_output);
    create_new_binstring(file, file_output, abc); // записываем бинарную строку в файл
    fseek(file_output, 0, SEEK_SET);
}

void create_decoded_file(FILE* file_outputRead, FILE* file_decoded) {
    BIT2CHAR symb;
    int countSym = 0;
    fread(&countSym, sizeof(int), 1, file_outputRead); // ОБЯЗАТЕЛЬНО ПЕРЕД read() ЧИТАЕМ КОЛ-ВО СИМВОЛОВ ДО КОДИРОВКИ

    clean_node* tree_for_decoding = read_Huffman(file_outputRead); // read() читает из закодированного файла дерево и возвращает корень, ПЕРЕД ЭТОЙ ФУНКЦИЕЙ ОБЯЗАТЕЛЬНО ПРОЧИТАТЬ countSym(количество символов без кодировки)
    unsigned char byte[8];
    clean_node* root = tree_for_decoding;
    printf("\n");
    while (fread(&symb.symb, sizeof(unsigned char), 1, file_outputRead)) {
        byte[0] = symb.mbit.b1;
        byte[1] = symb.mbit.b2;
        byte[2] = symb.mbit.b3;
        byte[3] = symb.mbit.b4;
        byte[4] = symb.mbit.b5;
        byte[5] = symb.mbit.b6;
        byte[6] = symb.mbit.b7;
        byte[7] = symb.mbit.b8;
        for (int i = BIT8 - 1; i >= 0 && countSym != 0; i--) {
            if (tree_for_decoding->isSym == 1) {
                putc(tree_for_decoding->symbol, file_decoded);
                tree_for_decoding = root;
                countSym--;
            }
            if (byte[i] == 0) {
                tree_for_decoding = tree_for_decoding->left;
            }
            else {
                tree_for_decoding = tree_for_decoding->right;
            }
        }
    }
}

void write_Huffman(node* avlleaf, FILE* f) {
    char flag = 1; 
    fwrite(&avlleaf->symbol, sizeof(char), 1, f);
    fwrite(&avlleaf->isSym, sizeof(char), 1, f);
    if (avlleaf->left != NULL) {
        fwrite(&flag, sizeof(char), 1, f);
        write_Huffman(avlleaf->left, f);
    }
    else {
        flag = 0;
        fwrite(&flag, sizeof(char), 1, f);
    }
    flag = 1;
    if (avlleaf->right != NULL) {
        fwrite(&flag, sizeof(char), 1, f);
        write_Huffman(avlleaf->right, f);
    }
    else {
        flag = 0;
        fwrite(&flag, sizeof(char), 1, f);
    }
}

clean_node* read_Huffman(FILE* f) {
    char flag;
    clean_node* avlleaf = create_clean_node();
    fread(&avlleaf->symbol, sizeof(char), 1, f);
    fread(&avlleaf->isSym, sizeof(char), 1, f);
    fread(&flag, sizeof(char), 1, f);
    if (flag == 1) avlleaf->left = read_Huffman(f);
    fread(&flag, sizeof(char), 1, f);
    if (flag == 1) avlleaf->right = read_Huffman(f);
    return avlleaf;
}

void init(unsigned char* arr) {
    for (int i = 0; i < SIZE; i++)
        arr[i] = '0';
}

void create_new_binstring(FILE* name, FILE* file_output, Alphabet* abc) {
    unsigned char c;
    // Читаем файл по байту и находим в массиве abc такой же байт и копируем его новый код в бинарную строку
    BIT2CHAR symb;
    int ind = 0;
    long long int count = 0;
    unsigned char string[SIZE];
    while (fread(&c, sizeof(unsigned char), 1, name)) {
        for (int i = 0; abc[c].code[i] != '\0'; i++) {
            string[ind++] = abc[c].code[i];
            if (ind == SIZE - 1) {
                for (int j = 0; j < SIZE / BIT8; j++) {
                    symb.mbit.b1 = string[j * BIT8 + 7];
                    symb.mbit.b2 = string[j * BIT8 + 6];
                    symb.mbit.b3 = string[j * BIT8 + 5];
                    symb.mbit.b4 = string[j * BIT8 + 4];
                    symb.mbit.b5 = string[j * BIT8 + 3];
                    symb.mbit.b6 = string[j * BIT8 + 2];
                    symb.mbit.b7 = string[j * BIT8 + 1];
                    symb.mbit.b8 = string[j * BIT8 + 0];
                    putc(symb.symb, file_output);
                }
                init(string);
                ind = 0;
            }
        }
        count++;
    }
    // Дозаписываем остаток
    if (count % BIT8 != 0) {
        for (int i = 0; i < SIZE; i++) {
            symb.mbit.b1 = string[i * BIT8 + 7];
            symb.mbit.b2 = string[i * BIT8 + 6];
            symb.mbit.b3 = string[i * BIT8 + 5];
            symb.mbit.b4 = string[i * BIT8 + 4];
            symb.mbit.b5 = string[i * BIT8 + 3];
            symb.mbit.b6 = string[i * BIT8 + 2];
            symb.mbit.b7 = string[i * BIT8 + 1];
            symb.mbit.b8 = string[i * BIT8 + 0];
            putc(symb.symb, file_output);
        }
    }
    fseek(name, 0, SEEK_SET);
};
