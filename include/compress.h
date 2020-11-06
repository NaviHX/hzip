#ifndef __COMPRESS_H__
#define __COMPRESS_H__

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include "bintree.h"

using namespace std;

#define BUFFER_SIZE 8

struct fileW
{
    FILE *out;
    string *encoding;
    char buffer[BUFFER_SIZE];
    int used;
};

struct fileR
{
    FILE *in;
    string *encoding;
    BYTE remainer;
};

fileW *getOutputFile(char *fileName); //获取输出文件结构
fileR *getInputFile(char *fileName);  //获取输入文件结构

int flushW(fileW *fout);                      //清除缓冲区
int fileWrite(fileW *fout, string bitString); //写入压缩文件

void compress(char *inputFileName, char *outputFileName); //压缩流程
void extract(char *inputFileName, char *outputFileName);  //解压流程

#endif
