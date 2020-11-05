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
    node *left;
    node *right;
    long long freq;
    BYTE val;
};

struct comp
{
    bool operator()(node *a, node *b)
    {
        return a->freq > b->freq;
    }
};

node *getNode(BYTE c, long long freq);
node *getHuffmanTree(int freq[]);
void deleteHuffmanTree(node *t);
void getEncoding(string* encoding,node* root,vector<char>& state);

#endif
