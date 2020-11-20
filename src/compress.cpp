#include "compress.h"

/*
获取输入文件结构
fileName: 输出文件名
*/
fileW *getOutputFile(char *fileName)
{
    fileW *ret = (fileW *)malloc(sizeof(fileW));
    ret->out = fopen(fileName, "wb");
    ret->encoding = NULL;
    ret->used = 0;
    memset(ret->buffer, 0, BUFFER_SIZE);
    return ret;
}

/*
获取输出文件结构
fileName: 输入文件名
*/
fileR *getInputFile(char *fileName)
{
    fileR *ret = (fileR *)malloc(sizeof(fileR));
    ret->in = fopen(fileName, "rb");
    ret->encoding = NULL;
    ret->remainer = 0;
    return ret;
}

/*
清除缓冲区
fout: 需要清除缓冲区的输出文件
ret-> 清除前缓冲区字符数
*/
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

/*
比特串写入压缩文件
fout: 写入文件结构
bitString: 待输入的比特串
ret-> 比特串长度 % 缓冲区大小
*/
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

/*
压缩文件
inputFileName: 输入文件名
outputFileName: 输出文件名
*/
void compress(char *inputFileName, char *outputFileName)
{
    fileR *fin = getInputFile(inputFileName);
    fileW *fout = getOutputFile(outputFileName);
    BYTE *buf;
    int count;
    BYTE freq[256];
    for (int i = 0; i < 256; i++)
        freq[i] = 0;
    //抽样前4k获取字符频率
    buf = (BYTE *)malloc(sizeof(BYTE) * 4 * 1024);
    count = fread(buf, sizeof(BYTE), 4 * 1024, fin->in);
    for (int i = 0; i < count; i++)
    {
        if (freq[buf[i]] != 0xffU)
            freq[buf[i]]++;
    }
    free(buf);
    fseek(fin->in, 0, SEEK_SET);
    node *hTree = getHuffmanTree(freq);
    string enc[256];
    vector<char> v;
    getEncoding(enc, hTree, v);
    fprintf(fout->out, "HZip");
    fseek(fout->out, 1, SEEK_CUR);
    fwrite(freq, sizeof(BYTE), 256, fout->out);
    fprintf(fout->out, "\0");
    buf = (BYTE *)malloc(sizeof(BYTE) * 1024);
    while (!feof(fin->in))
    {
        count = fread(buf, sizeof(BYTE), 1024, fin->in);
        for (int i = 0; i < count; i++)
            fileWrite(fout, enc[buf[i]]);
    }
    BYTE remainer = flushW(fout);
    fseek(fout->out, 4, SEEK_SET);
    fwrite(&remainer, sizeof(BYTE), 1, fout->out);
    deleteHuffmanTree(hTree);
    free(buf);
    fclose(fin->in);
    fclose(fout->out);
}

/*
解压文件
inputFileName: 输入文件名
outputFileName: 输出文件名
*/
void extract(char *inputFileName, char *outputFileName)
{
    fileR *fin = getInputFile(inputFileName);
    fileW *fout = getOutputFile(outputFileName);
    char verify[4];
    queue<char> q;
    BYTE freq[256];
    int count;
    BYTE *buf;
    node *cur;
    count = fread(verify, sizeof(char), 5, fin->in);
    if (!(verify[0] == 'H' && verify[1] == 'Z' && verify[2] == 'i' && verify[3] == 'p'))
    {
        cout << "Error File!\nNot a Hzip file\n";
        return;
    }
    fin->remainer = verify[4];
    if (fin->remainer == 0)
        fin->remainer = 8;
    count = fread(freq, sizeof(BYTE), 256, fin->in);
    if (count < 256)
    {
        cout << "This Hzip File is Corrupt !!!\n";
        return;
    }
    node *root = getHuffmanTree(freq);
    buf = (BYTE *)malloc(sizeof(BYTE) * 1024);
    cur = root;
    while (count = fread(buf, sizeof(BYTE), 1024, fin->in))
    {
        int maxSize = 8;
        BYTE temp;
        for (int i = 0; i < count - 1; i++)
        {
            temp = buf[i];
            for (int j = 0; j < maxSize; j++)
            {
                q.push((temp & 1) + '0');
                temp >>= 1;
            }
        }
        maxSize = (feof(fin->in)) ? fin->remainer : 8;
        temp = buf[count - 1];
        for (int i = 0; i < maxSize; i++)
        {
            q.push((temp & 1) + '0');
            temp >>= 1;
        }
        while (!q.empty())
        {
            temp = q.front();
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
    if (cur != root)
        cout << "This Hzip File is Corrupt !!!\nBut Hzip can still extract it.\n";
    deleteHuffmanTree(root);
    fclose(fin->in);
    fclose(fout->out);
}
