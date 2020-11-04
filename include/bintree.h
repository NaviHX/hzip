#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <queue>
#include <cstdlib>

#define MAX_CHAR 256
typedef unsigned char BYTE;

struct node
{
    node *left;
    node *right;
    long long freq;
    BYTE val;

    bool operator<(node a, node b)
    {
        a->freq < b->freq;
    }
};

struct comp
{
    bool operator()(node *a, node *b)
    {
        return a->freq > b->right;
    }
};

node *getNode(BYTE c, long long freq);
node *getHuffmanTree(int freq[]);
void deleteHuffmanTree(node *t);

#endif
