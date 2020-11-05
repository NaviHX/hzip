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
        temp += (fout->buffer[BUFFER_SIZE - i - 1] - '0');
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
        q.pop();
    }
    return (pre + bitString.size()) % BUFFER_SIZE;
}

void compress(char *inputFileName, char *outputFileName)
{
    fileR *fin = getInputFile(inputFileName);
    fileW *fout = getOutputFile(outputFileName);
    long long freq[256];
    for (int i = 0; i < 256; i++)
        freq[i] = 0;
    while (!feof(fin->in))
    {
        BYTE temp;
        fscanf(fin->in, "%c", &temp);
        freq[temp]++;
    }
    fseek(fin->in, 0, SEEK_SET);
    node *hTree = getHuffmanTree(freq);
    string enc[256];
    vector<char> v;
    getEncoding(enc, hTree, v);
    fprintf(fout->out, "HZip\0");
    fwrite(freq, sizeof(long long), 256, fout->out);
    fprintf(fout->out, "\0");
    while (!feof(fin->in))
    {
        BYTE temp;
        fscanf(fin->in, "%c", &temp);
        fileWrite(fout, enc[temp]);
    }
    BYTE remainer = flushW(fout);
    fseek(fout->out, 4, SEEK_SET);
    fprintf(fout->out, "%c", remainer);
}

void extract(char *inputFileName, char *outputFileName)
{
    fileR *fin = getInputFile(inputFileName);
    fileW *fout = getOutputFile(outputFileName);
    char verify[5];
    queue<char> q;
    long long freq[256];
    verify[4] = '\0';
    fscanf(fin->in, "%c%c%c%c", verify, verify + 1, verify + 2, verify + 3);
    if (!(verify[0] == 'H' && verify[1] == 'Z' && verify[2] == 'i' && verify[3] == 'p'))
    {
        cout << "Error File!\nNot a Hzip file\n";
        return;
    }
    fscanf(fin->in, "%c", fin->remainer);
    fread(freq, sizeof(long long), 256, fin->in);
    node *root = getHuffmanTree(freq);
    while (!feof(fin->in))
    {
        BYTE temp, maxSize = 8;
        fscanf(fin->in, "%c", &temp);
        maxSize = (feof(fin->in)) ? fin->remainer : maxSize;
        for (int i = 0; i < maxSize; i++)
        {
            q.push('0' + (temp & 1));
            temp >>= 1;
        }
    }
    node *cur = root;
    while (!q.empty())
    {
        char temp = q.front();
        cur = temp == '0' ? cur->left : cur->right;
        if (cur == NULL)
        {
            cout << "This Hzip File is Corrupt !!!\n";
            return;
        }
        if (cur->left == NULL && cur->right == NULL)
        {
            fprintf(fout->out, "%c", cur->val);
            cur = root;
        }
        q.pop();
    }
}
