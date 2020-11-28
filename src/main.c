#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "HuffmanTree.h"
#include "operation.h"

int main() {
    HuffmanTree HT = NULL;
    HuffmanCode HC = NULL;
    int x;
    int run = 1;
    int n = 0;
    Function func = INVALID;
    while (run) {
        char ch = INVALID;
        puts("I(Initialization)  E(Encoding)  D(Decoding)  P(Print)  T(Tree Printing)  Q(Quit)\nInput:");
        x = scanf("%c", &ch);
        while (getchar() != '\n');
        func = ch;
        switch (func)
        {
        case INITIALIZATION:
            initialization(&HT, &HC, &n);
            break;

        case ENCODING:
            encoding(&HT, &HC, &n);
            break;

        case DECODING:
            decoding(&HT, &HC, &n);
            break;

        case PRINT:
            print();
            break;

        case TREEPRINTING:
            treePrint(&HT, &HC, &n);
            break;

        case GEFFILE:
            geffile(&HT, &HC, &n);
            break;

        case CODETABLE:
            codetable(&HT, &HC, &n);
            break;

        case QUIT:
            puts("Over.");
            run = 0;
            break;

        default:
            puts("Invalid input.");
            break;
        }
    }
    if (HT != NULL)
        destroyHT(HT);
    if (HC != NULL)
        destroyHC(HC, n);
    return 0;
}
