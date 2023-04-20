#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define BIT8 8
#define SIZE 257

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct alphabet {
    char code[SIZE]; 
    unsigned char sym; 
} Alphabet;

typedef union bit2char {
    unsigned char symb;
    struct bit {
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