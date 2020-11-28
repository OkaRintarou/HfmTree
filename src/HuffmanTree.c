#define _CRT_SECURE_NO_WARNINGS

#include "HuffmanTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HuffmanTree createHuffmanTree(int n, Method method, char* filename)
{
    if (n <= 1)
    {
        puts("Invalid input.");
        return NULL;
    }

    HuffmanTree HT = calloc(2ll * n, sizeof(HTNode));

    switch (method) {

    case fileComplete:
        loadFromFile(HT, n, fileComplete, filename);
        break;

    case file:
        loadFromFile(HT, n, file, filename);
        generate(HT, n);
        outputTree(HT, 2 * n - 1, filename);
        break;

    case stdinInput:
    default:
        input(HT, n);
        generate(HT, n);
        outputTree(HT, 2 * n - 1, filename);
        break;
    }

    return HT;
}

void input(HuffmanTree HT, int n)
{
    int x;
    puts("format:%c %d\\n");
    for (int i = 1; i <= n; ++i) {
        HT[i].ch = getchar();
        x = scanf(" %d", &HT[i].weight);
        while (getchar() != '\n');
    }
}

void generate(HuffmanTree HT, int n)
{
    for (int i = n + 1; i <= 2 * n - 1; ++i)
    {
        int s1 = 0, s2 = 0;
        select(HT, i - 1, &s1, &s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lch = s1;
        HT[i].rch = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void select(HuffmanTree HT, int i, int* s1, int* s2)
{
    typedef struct Min {
        int weight;
        int s;
    }Min;

    Min min[2] = { 0 };

    for (int j = 1; j <= i; j++)
    {
        if (HT[j].parent == 0) {
            if (min[0].s == 0) {
                min[0].s = j;
                min[0].weight = HT[j].weight;
            }
            else if (min[1].s == 0) {
                min[1].s = j;
                min[1].weight = HT[j].weight;
            }
            else if (HT[j].weight < min[0].weight)
            {
                min[0].weight = HT[j].weight;
                min[0].s = j;
            }
            else if (HT[j].weight < min[1].weight)
            {
                min[1].weight = HT[j].weight;
                min[1].s = j;
            }
        }
    }
    *s1 = min[0].s;
    *s2 = min[1].s;
}

void printTreeW(HuffmanTree HT, int s, int depth, FILE* fp)
{
    if (s == 0)return;
    for (int i = 1; i < depth; i++)
    {
        fprintf(fp, "\t");
        fprintf(stdout, "\t");
    }
    if (HT[s].lch == 0) {
        fprintf(fp, "%d(%c)\n", HT[s].weight, HT[s].ch);
        fprintf(stdout, "%d(%c)\n", HT[s].weight, HT[s].ch);
    }
    else {
        fprintf(fp, "%d\n", HT[s].weight);
        fprintf(stdout, "%d\n", HT[s].weight);
    }
    printTreeW(HT, HT[s].lch, depth + 1, fp);
    printTreeW(HT, HT[s].rch, depth + 1, fp);
}

void printTree(HuffmanTree HT, int s, char* filename)
{
    FILE* fp = fopen(filename, "w");
    s = 2 * s - 1;
    printTreeW(HT, s, 1, fp);
    fclose(fp);
}


void loadFromFile(HuffmanTree HT, int n, Method method, char* filename)
{
    int x;

    FILE* fp = fopen(filename, "r");

    if (fp == NULL)
        return;

    if (HT == NULL)
        return;

    int m;
    switch (method) {
    case file:
        m = n + 1;
        break;

    default:
        m = 2 * n;
        break;
    }

    for (int i = 1; i < m; i++)
    {
        HT[i].ch = fgetc(fp);
        x = fscanf(fp, " %d %d %d %d", &HT[i].weight, &HT[i].parent, &HT[i].lch, &HT[i].rch);
        fgetc(fp);
    }

    fclose(fp);
}

void outputTree(HuffmanTree HT, int n, char* filename)
{
    FILE* fp = fopen(filename, "w");

    for (int i = 1; i <= n; i++)
    {
        fprintf(fp, "%c %d %d %d %d\n", HT[i].ch, HT[i].weight, HT[i].parent, HT[i].lch, HT[i].rch);
    }

    fclose(fp);
}

void encode(HuffmanCode HC, int n, FILE* src, FILE* trg)
{
    char ch;
    char buffer[9] = { 0 };
    int size = 0;
    int flag = 0;
    char bbuf[9] = { 0 };
    int k = 0, p = 0, length = 0;
    while (ch = fgetc(src), ch != EOF) {
        for (int i = 1; i < n + 1; i++)
        {
            if (ch == HC[i].ch) {
                length = strlen(HC[i].code);
                if (length + size <= 8) {
                    strcat(buffer, HC[i].code);
                    size += length;
                }
                else {
                    k = 0;
                    for (int j = size; j < 8; j++)
                    {
                        buffer[j] = HC[i].code[k];
                        k++;
                    }
                    p = 0;
                    for (; (k < length) && (p < 8); k++)
                    {
                        bbuf[p] = HC[i].code[k];
                        p++;
                    }
                    size = 8;
                    flag = 1;
                }
                if (size == 8) {
                    size = 0;
                    char code = 0;
                    for (int i = 0; i < 8; i++)
                    {
                        code <<= 1;
                        code |= buffer[i] - '0';
                    }
                    fprintf(trg, "%c", code);
                    memset(buffer, 0, 9);
                }
                while (flag) {
                    strcpy(buffer, bbuf);
                    memset(bbuf, 0, 9);
                    p = 0;
                    size = strlen(buffer);
                    if (size == 8) {
                        size = 0;
                        char code = 0;
                        for (int i = 0; i < 8; i++)
                        {
                            code <<= 1;
                            code |= buffer[i] - '0';
                        }
                        fprintf(trg, "%c", code);
                        memset(buffer, 0, 9);
                    }
                    for (; (k < length) && (p < 8); k++)
                    {
                        bbuf[p] = HC[i].code[k];
                        p++;
                    }
                    if ((k == length)&&(strlen(bbuf)==0))
                    {
                        flag = 0;
                    }
                }
                break;
            }
        }
    }
    size = strlen(buffer);
    if (size != 0) {
        char l = 8 - size;
        for (int i = size; i < 8; i++)
        {
            buffer[i] = '0';
        }
        char code = 0;
        for (int i = 0; i < 8; i++)
        {
            code <<= 1;
            code |= buffer[i] - '0';
        }
        fprintf(trg, "%c%c", code, l);
    }
    else {
        fprintf(trg, "%c", 0);
    }
}

void printCodeTable(HuffmanCode HC, int n, char* filename)
{
    FILE* fp = fopen(filename, "w");
    for (int i = 1; i < n + 1; i++)
    {
        printf("%c %s\n", HC[i].ch, HC[i].code);
        fprintf(fp, "%c %s\n", HC[i].ch, HC[i].code);
    }
    fclose(fp);
}

void decode(HuffmanTree HT, int n, FILE* src, char* filename)
{
    FILE* fp = fopen(filename, "w");
    char ch1, ch2;
    char buffer[9] = { 0 };
    char bbuf[9] = { 0 };
    int flag = 0;
    int m = 2 * n - 1;
    int p;
    ch2 = fgetc(src);
    fgetc(src);
    do {
        fseek(src, -1, SEEK_CUR);
        ch1 = ch2;
        ch2 = fgetc(src);
        fgetc(src);
        if (!feof(src)) {
            strcpy(buffer, bbuf);
            int length = strlen(buffer);
            int i = length;
            int k = 0;
            for (; i < 8; i++)
            {
                buffer[i] = (((ch1 & 0x80) >> 7) & 1) + '0';
                ch1 <<= 1;
                k++;
            }
            for (; k < 8; k++)
            {
                bbuf[i] = (((ch1 & 0x80) >> 7) & 1) + '0';
                ch1 <<= 1;
            }
            if (!flag)
                p = m;
            for (int j = 0; j < 8; j++)
            {
                if (isLeaf(&HT[p]))
                {
                    fprintf(fp, "%c", HT[p].ch);
                    p = m;
                    j--;
                }
                else {
                    if (buffer[j] == '0')
                        p = HT[p].lch;
                    else
                        p = HT[p].rch;
                }
            }
            if (isLeaf(&HT[p])) {
                fprintf(fp, "%c", HT[p].ch);
                p = m;
                flag = 0;
            }
            else {
                flag = 1;
            }
        }
        else {
            memset(buffer, 0, 9);
            for (int i = 0; i < 8 - ch2; i++)
            {
                buffer[i] = (((ch1 & 0x80) >> 7) & 1) + '0';
                ch1 <<= 1;
            }
            if (!flag)
                p = m;
            for (int i = 0; i < strlen(bbuf); i++) {
                if (isLeaf(&HT[p]))
                {
                    fprintf(fp, "%c", HT[p].ch);
                    p = m;
                    i--;
                }
                else {
                    if (bbuf[i] == '0')
                        p = HT[p].lch;
                    else
                        p = HT[p].rch;
                }
            }
            for (int i = 0; i < strlen(buffer); i++) {
                if (isLeaf(&HT[p]))
                {
                    fprintf(fp, "%c", HT[p].ch);
                    p = m;
                    i--;
                }
                else {
                    if (buffer[i] == '0')
                        p = HT[p].lch;
                    else
                        p = HT[p].rch;
                }
            }
            fprintf(fp, "%c", HT[p].ch);
        }
    } while (!feof(src));
    fclose(fp);
}

void printCode(FILE* code, char* trg)
{
    FILE* fp = fopen(trg, "w");
    char str[51] = { 0 };
    int i = 0;
    int j = 0;
    int flag = 0;
    int fend = 0;
    char ch1, ch2;
    ch1 = fgetc(code);
    ch2 = fgetc(code);
    do {
        if (flag != 1) {
            flag = fgetc(code) == -1;
            fseek(code, -1, SEEK_CUR);
        }
        if (strlen(str) == 50) {
            fprintf(stdout, "%s\n", str);
            fprintf(fp, "%s\n", str);
            memset(str, 0, 51);
            i = 0;
        }
        if (!flag) {
            if (j < 8) {
                str[i] = (((ch1 & 0x80) >> 7) & 1) + '0';
                ch1 <<= 1;
                i++;
                j++;
            }
            else {
                j = 0;
                ch1 = ch2;
                ch2 = fgetc(code);
            }
        }
        else {
            if (j < 8 - ch2) {
                str[i] = (((ch1 & 0x80) >> 7) & 1) + '0';
                ch1 <<= 1;
                i++;
                j++;
            }
            else {
                fend = 1;
            }
        }
    } while (!fend);
    if (strlen(str) != 0) {
        fprintf(stdout, "%s\n", str);
        fprintf(fp, "%s\n", str);
    }
    fclose(fp);
}

void destroyHT(HuffmanTree HT)
{
    free(HT);
}

void destroyHC(HuffmanCode HC, int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        free(HC[i].code);
    }
    free(HC);
}

int isLeaf(HuffmanTree HT)
{
    return HT->lch == 0 && HT->rch == 0;
}

HuffmanCode createHfmCode(HuffmanTree HT, int n) {
    HuffmanCode HC = calloc(sizeof(HCNode), n + 1ll);
    if (HC == NULL)
        return HC;
    for (int i = 1; i < n + 1; i++)
    {
        HC[i].ch = HT[i].ch;
        HC[i].code = calloc(sizeof(char), n + 1ll);
        int p = HT[i].parent;
        int j = 0;
        int tmp = i;
        while (p != 0) {
            if (HT[p].lch == tmp)
                HC[i].code[j] = '0';
            else
                HC[i].code[j] = '1';
            j++;
            tmp = p;
            p = HT[p].parent;
        }
        HC[i].code = _strrev(HC[i].code);
    }
    return HC;
}
