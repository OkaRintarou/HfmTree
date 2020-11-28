#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <stdio.h>

typedef struct HuffmanTree
{
    char ch;
    int weight;
    int parent, lch, rch;
}HTNode, * HuffmanTree;

typedef enum Method {
    stdinInput,
    file,
    fileComplete
}Method;

typedef struct HuffmanCode {
    char ch;
    char* code;
}HCNode, * HuffmanCode;

HuffmanCode createHfmCode(HuffmanTree HT, int n);

void input(HuffmanTree HT, int n);

void generate(HuffmanTree HT, int n);

HuffmanTree createHuffmanTree(int n, Method method, char* filename);

void select(HuffmanTree HT, int i, int* s1, int* s2);

void printTree(HuffmanTree HT, int s, char* filename);

void printTreeW(HuffmanTree HT, int s, int depth, FILE* fp);

void loadFromFile(HuffmanTree HT, int n, Method method, char* filename);

void outputTree(HuffmanTree HT, int n, char* filename);

void encode(HuffmanCode HC, int n, FILE* src, FILE* trg);

void printCodeTable(HuffmanCode HC, int n, char* filename);

void decode(HuffmanTree HT, int n, FILE* src, char* filename);

void printCode(FILE* code, char* trg);

void destroyHT(HuffmanTree HT);

void destroyHC(HuffmanCode HC, int n);

int isLeaf(HuffmanTree HT);
