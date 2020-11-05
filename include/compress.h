#ifndef __COMPRESS_H__
#define __COMPRESS_H__

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include "bintree.h"

using namespace std;

#define BUFFER_SIZE 8

struct fileW{
    FILE* out;
    string* encoding;
    char buffer[BUFFER_SIZE];
    int used;
};

struct fileR{
    FILE* in;
    string* encoding;
    int remainer;
};

fileW* getOutputFile(char* fileName);
fileR* getInputFile(char* fileName);

int flushW(fileW* fout);
int fileWrite(fileW* fout,string bitString);

void compress(string inputFileName,string outputFileName);
void extract(string inputFileName,string outputFileName);

#endif
