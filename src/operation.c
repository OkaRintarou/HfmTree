#define _CRT_SECURE_NO_WARNINGS

#include "operation.h"
#include <stdio.h>

void codetable(HuffmanTree* pHT, HuffmanCode* pHC, int* n)
{
    int x;
    string filename;
    if (*pHT == NULL) {
        puts("No HuffmanTree exists. Please input the file name where HT is:");
        mfgets(filename, STRL, stdin);
        puts("Input the size of character sort:");
        x = scanf("%d", n);
        while (getchar() != '\n');
        *pHT = createHuffmanTree(*n, fileComplete, filename);
        *pHC = createHfmCode(*pHT, *n);
    }
    puts("Input the file name where codetable will be saved:");
    mfgets(filename, STRL, stdin);
    printCodeTable(*pHC, *n, filename);
}

void initialization(HuffmanTree* pHT, HuffmanCode* pHC, int* n) {
    int x;
    puts("Input the size of character sort:");
    x = scanf("%d", n);
    while (getchar() != '\n');
    puts("Input the file name where hfmTree will be saved:");
    string filename;
    mfgets(filename, STRL, stdin);
    *pHT = createHuffmanTree(*n, stdinInput, filename);
    *pHC = createHfmCode(*pHT, *n);
}

void encoding(HuffmanTree* pHT, HuffmanCode* pHC, int* n)
{
    int x;
    if (*pHT == NULL) {
        puts("No HuffmanTree exists. Please input the file name where HT is:");
        string filename;
        mfgets(filename, STRL, stdin);
        puts("Input the size of character sort:");
        x = scanf("%d", n);
        while (getchar() != '\n');
        *pHT = createHuffmanTree(*n, fileComplete, filename);
        *pHC = createHfmCode(*pHT, *n);
    }
    string src;
    string trg;
    puts("Input the src file name:");
    mfgets(src, STRL, stdin);
    puts("Input the trg file name:");
    mfgets(trg, STRL, stdin);
    FILE* fsrc = fopen(src, "r");
    FILE* ftrg = fopen(trg, "w");
    encode(*pHC, *n, fsrc, ftrg);
    fclose(fsrc);
    fclose(ftrg);
}

void decoding(HuffmanTree* pHT, HuffmanCode* pHC, int* n)
{
    int x;
    if (*pHT == NULL) {
        puts("No HuffmanTree exists. Please input the file name where HT is:");
        string filename;
        mfgets(filename, STRL, stdin);
        puts("Input the size of character sort:");
        x = scanf("%d", n);
        while (getchar() != '\n');
        *pHT = createHuffmanTree(*n, fileComplete, filename);
        *pHC = createHfmCode(*pHT, *n);
    }
    puts("Input the file name where codetext saved:");
    string code;
    mfgets(code, STRL, stdin);
    puts("Input the file name where text will be saved:");
    string text;
    mfgets(text, STRL, stdin);
    FILE* fp = fopen(code, "r");
    decode(*pHT, *n, fp, text);
    fclose(fp);
}

void print()
{
    puts("Input the file name where codefile saved:");
    string filename;
    mfgets(filename, STRL, stdin);
    puts("Input the file name where codefile in characters will be saved:");
    string trg;
    mfgets(trg, STRL, stdin);
    FILE* fp = fopen(filename, "r");
    printCode(fp, trg);
    fclose(fp);
}

void treePrint(HuffmanTree* pHT, HuffmanCode* pHC, int* n)
{
    int x;
    string filename;
    if (*pHT == NULL) {
        puts("No HuffmanTree exists. Please input the file name where HT is:");
        mfgets(filename, STRL, stdin);
        puts("Input the size of character sort:");
        x = scanf("%d", n);
        while (getchar() != '\n');
        *pHT = createHuffmanTree(*n, fileComplete, filename);
        *pHC = createHfmCode(*pHT, *n);
    }
    puts("Input the file name where the graph of hfmTree will be saved:");
    mfgets(filename, STRL, stdin);
    printTree(*pHT, *n, filename);
}

void geffile(HuffmanTree* pHT, HuffmanCode* pHC, int* n)
{
    int x;
    string filename;
    puts("Input the file name where hfmTree saved:");
    mfgets(filename, STRL, stdin);
    puts("Input the size of character sort:");
    x = scanf("%d", n);
    while (getchar() != '\n');
    *pHT = createHuffmanTree(*n, file, filename);
    *pHC = createHfmCode(*pHT, *n);
}

char* mfgets(char* buffer, int count, FILE* stream)
{
    char* result = fgets(buffer, count, stream);
    int i = 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
        i++;
    }
    return result;
}
