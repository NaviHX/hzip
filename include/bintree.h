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
        if (a->freq != b->freq)
            return a->freq > b->freq;
        else
            return a->val > b->val;
    }
};

node *getNode(BYTE c, long long freq);
node *getHuffmanTree(BYTE freq[]);
void deleteHuffmanTree(node *t);
void getEncoding(std::string *encoding, node *root, std::vector<char> &state);

#endif
