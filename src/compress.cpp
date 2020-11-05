#include "compress.h"

fileW *getOutputFile(char *fileName)
{
    fileW *ret = (fileW *)malloc(sizeof(fileW));
    ret->out = fopen(fileName, "w");
    ret->encoding = NULL;
    ret->used = 0;
    memset(ret->buffer, 0, BUFFER_SIZE);
    return ret;
}

fileR *getInputFile(char *fileName)
{
    fileR *ret = (fileR *)malloc(sizeof(fileR));
    ret->in = fopen(fileName, "r");
    ret->encoding = NULL;
    ret->remainer = 0;
    return ret;
}

int flushW(fileW *fout)
{
    if (fout->used == 0)
        return 0;
    int ret = fout->used;
    BYTE temp = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        temp <<= 1;
        temp += (fout->buffer[i] - '0');
    }
    fout->out &&fwrite(&temp, 1, 1, fout->out);
    fout->used = 0;
    memset(fout->buffer, 0, BUFFER_SIZE);
    return ret;
}

int fileWrite(fileW *fout, string bitString)
{
    int pre = fout->used;
    queue<char> q;
    for (int i = 0; i < bitString.size(); i++)
        q.push(bitString[i]);
    while (!q.empty())
    {
        if (fout->used == BUFFER_SIZE)
            flushW(fout);
        char temp = q.front();
        fout->buffer[fout->used] = temp;
        fout->used++;
    }
    return (pre + bitString.size()) % BUFFER_SIZE;
}

void compress(char *inputFileName, char *outputFileName)
{
    fileR *fin = getInputFile(inputFileName);
    fileW *fout = getOutputFile(outputFileName);
    long long freq[256];
    while(!feof(fin->in))
    {
        BYTE temp;
        fscanf(fin->in,"%c",&temp);
        freq[temp]++;
    }
    fseek(fin->in,0,SEEK_SET);
    node* hTree=getHuffmanTree(freq);
    string encoding[256];
    vector<char> v;
    getEncoding(encoding,hTree,v);
    fprintf(fout->out,"HZip\0");
    for(int i=0;i<256;i++)
        fprintf(fout->out,"lld",freq[i]);
    fprintf(fout->out,"\0");
    while(!feof(fin->in))
    {
        BYTE temp;
        fscanf(fin->in,"%c",&temp);
        fileWrite(fout,encoding[temp]);
    }
    BYTE remainer=flushW(fout);
    fseek(fout->out,4,SEEK_SET);
    fprintf(fout->out,"%c",remainer);
}
