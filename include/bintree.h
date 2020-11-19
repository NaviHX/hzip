#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <queue>
#include <cstdlib>
#include <vector>
#include <string>

#define MAX_CHAR 256
typedef unsigned char BYTE;

struct node
{
    node *left;     //左子节点
    node *right;    //右子节点
    long long freq; //频率
    BYTE val;       //权值
};

struct comp
{
    bool operator()(node *a, node *b)
    {
        if (a->freq != b->freq)
            return a->freq > b->freq;
        else
            return a->val > b->val;
    }
};

node *getNode(BYTE c, long long freq);                                         //获取节点
node *getHuffmanTree(BYTE freq[]);                                             //获取哈夫曼树
void deleteHuffmanTree(node *t);                                               //释放哈夫曼树
void getEncoding(std::string *encoding, node *root, std::vector<char> &state); //遍历哈夫曼树获取编码表,存储在encoding字符串组中

#endif
