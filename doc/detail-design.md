# 详细设计

node *getNode(BYTE c, long long freq)
获取并初始化一个节点
```c++
node *getNode(BYTE c, long long freq)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->freq = freq;
    temp->val = c;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
```

node *getHuffmanTree(BYTE freq[])
获取哈夫曼树
freq[]: 频率表
ret-> 树的根指针
```c++
node *getHuffmanTree(BYTE freq[])
{
    //获取一个小根堆
    for (int i = 0; i < MAX_CHAR; i++)
    {
        node *temp = getNode((BYTE)i, freq[i]);
        heap.push(temp);
    }
    while (heap.size() > 1)
    {
        //取出最小的两个节点
        //连接成一棵树
        //将新树加入堆
    }
    return heap.top();
}
```

void deleteHuffmanTree(node *t)
删除哈夫曼树
t: 待删除的哈夫曼树
```c++
void deleteHuffmanTree(node *t)
{
    if (t == NULL)
        return;
    deleteHuffmanTree(t->left);
    deleteHuffmanTree(t->right);
    free(t);
}
```

void getEncoding(string *encoding, node *root, vector<char> &state)
获取编码表
encoding: 用于保存编码表的字符串组
root: 当前的节点
state: 从根节点到当前节点的路径产生的比特串
```c++
void getEncoding(string *encoding, node *root, vector<char> &state)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL) //到达叶子节点
        {
            //将state保存到encoding相应的位置
        }
        else
        {
            if (root->left != NULL)
            {
                state.push_back('0');
                getEncoding(encoding, root->left, state);
                state.pop_back();
            }
            if (root->right != NULL)
            {
                state.push_back('1');
                getEncoding(encoding, root->right, state);
                state.pop_back();
            }
        }
    }
    return;
}
```

fileW *getOutputFile(char *fileName)
获取输入文件结构
fileName: 输出文件名
```c++
fileW *getOutputFile(char *fileName)
{
    fileW *ret = (fileW *)malloc(sizeof(fileW));
    ret->out = fopen(fileName, "wb");
    ret->encoding = NULL;
    ret->used = 0;
    memset(ret->buffer, 0, BUFFER_SIZE);
    return ret;
}
```

fileR *getInputFile(char *fileName)
获取输出文件结构
fileName: 输入文件名
```c++
fileR *getInputFile(char *fileName)
{
    fileR *ret = (fileR *)malloc(sizeof(fileR));
    ret->in = fopen(fileName, "rb");
    ret->encoding = NULL;
    ret->remainer = 0;
    return ret;
}
```

int flushW(fileW *fout)
清除缓冲区
fout: 需要清除缓冲区的输出文件
ret-> 清除前缓冲区字符数
```c++
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
```

int fileWrite(fileW *fout, string bitString)
比特串写入压缩文件
fout: 写入文件结构
bitString: 待输入的比特串
ret-> 比特串长度 % 缓冲区大小
```c++
int fileWrite(fileW *fout, string bitString)
{
    int pre = fout->used;
    queue<char> q;
    for (int i = 0; i < bitString.size(); i++)
        q.push(bitString[i]);
    while (!q.empty())
    {
        if (fout->used == BUFFER_SIZE) //缓冲区溢出
            //清除缓冲区
        char temp = q.front();
        fout->buffer[fout->used] = temp;
        fout->used++;
        q.pop();
    }
    return (pre + bitString.size()) % BUFFER_SIZE;
}
```

void compress(char *inputFileName, char *outputFileName)
压缩文件
inputFileName: 输入文件名
outputFileName: 输出文件名
```c++
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
    //构建哈夫曼树
    //获取编码表
    while (!feof(fin->in))
    {
        count=fread(buf,sizeof(BYTE),1024,fin->in);
        for(int i=0;i<count;i++)
            fileWrite(fout,enc[buf[i]]);
    }
    BYTE remainer = flushW(fout);
    fseek(fout->out, 4, SEEK_SET);
    fwrite(&remainer, sizeof(BYTE), 1, fout->out);
    fclose(fin->in);
    fclose(fout->out);
}
```

void extract(char *inputFileName, char *outputFileName)
解压文件
inputFileName: 输入文件名
outputFileName: 输出文件名
```c++
void extract(char *inputFileName, char *outputFileName)
{
    fileR *fin = getInputFile(inputFileName);
    fileW *fout = getOutputFile(outputFileName);
    char verify[4];
    queue<char> q;
    BYTE freq[256];
    int count;
    //检查校验字
    fin->remainer = verify[4];
    if (fin->remainer == 0)
        fin->remainer = 8;
    //检查频率表
    //构建哈夫曼树
    BYTE temp, maxSize = 8, sta, nxt;
    sta = fscanf(fin->in, "%c", &nxt);
    while (!feof(fin->in))
    {
        //文件内容加入队列
    }
    node *cur = root;
    while (!q.empty())
    {
        //获取比特
        //根据比特值在树上移动
        if(到达叶子)
            //输出叶子结点的字符
    }
    if(cur!=root)
        cout << "This Hzip File is Corrupt !!!\nBut Hzip can still extract it.\n";
    fclose(fin->in);
    fclose(fout->out);
}
```
