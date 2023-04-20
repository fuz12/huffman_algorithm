#define _CRT_SECURE_NO_WARNINGS

#include <wchar.h>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>
#include "priority_queue.h"
#include "defines.h"
#include "nodes.h"
#include "huffmanTree.h"
#include "write_read_file.h"

int main(void) {
    
    SetConsoleCP(1251);       
    SetConsoleOutputCP(1251);

    int choice = 0;
    char output[SIZE] = "output_encoded";

    // Храним коды файла
    int size = 0; // Кол-во уникальных значений
    Alphabet abc[SIZE];

    // Делаем выбор, что хотим сделать
    printf("What do you want to do?\n Choose:\n(1) Encoded the file\n(2) Decoded the file\nWrite the number of action: ");
    scanf("%d", &choice);

    if(choice == 1){

        printf("Input file name: \n");
        char file_input[SIZE];
        scanf("%s", file_input);

        // Открываем входной и выходной файлы
        FILE *file = fopen(file_input, "rb");
        FILE *file_output = fopen(output, "wb");        
        if(file == NULL){
            printf("Error input");
            exit(EXIT_FAILURE);
        }
        priority_queue* Q = create_pri_queue();
        int freq[SIZE] = {0}; // Частотный словарь

        int len = 0; // Кол-во использованных букв в файле

        unsigned char ch; // Переменная для записи прочитанного байта

        // Читаем файл и создаём частотный словарь
        while(fread(&ch, sizeof(unsigned char), 1, file)){
            freq[ch]++;
        }
        fseek(file, 0, SEEK_SET); // После прочтения файла переводим указатель в начало файла

        // Заполняем очередь с приоритетом, используя только что созданный частотный словарь
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

        node* tree = huffmanTree(Q, len); // Создаем Хаффман дерево
        node* tree_for_trip = cpy_node(tree);
        trip(tree_for_trip, abc, size); // Находим коды для записи каждого байта и сохраняем в abc
        int countSym = tree->frequency;
        create_encoded_file(file_output, file, countSym, tree, abc);

        printf("\nSuccess!\n");
        printf("Please enter any key to exit...\n");
        _getch();

        free_queue(Q);
        fclose(file);
        fclose(file_output);
    }



/*Декодируем закодированный файл || Все закодированный файлы без разрешения и называются "output_encoded"*/
    if(choice == 2){
        char decoded[SIZE];
        printf("Write the output file name: \n");
        scanf("%s", decoded);
        FILE* file_outputRead = fopen(output, "rb");
        FILE* file_decoded = fopen(decoded, "wb");
        if (file_outputRead == NULL) {
            printf("Error decoded");
            exit(EXIT_FAILURE);
        }
        create_decoded_file(file_outputRead, file_decoded);

        printf("\nSuccess!\n");
        printf("Please enter any key to exit...\n");

        fclose(file_decoded);
        fclose(file_outputRead);
    }

    return 0;
}