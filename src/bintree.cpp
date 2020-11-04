#include "bintree.h"

using namespace std;

node *getNode(BYTE c, long long freq)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->freq = freq;
    temp->val = c;
    return temp;
}

node *getHuffmanTree(long long freq[])
{
    priority_queue<node *, vector<node *>, comp> heap;
    for (int i = 0; i < MAX_CHAR; i++)
    {
        node *temp = getNode((BYTE)i, freq[i]);
        heap.push(temp);
    }
    while (heap.size() > 1)
    {
        node *tmp1 = heap.top();
        heap.pop();
        node *tmp2 = heap.top();
        heap.pop();
        node *root = getNode('\0', tmp1->freq + tmp2->freq);
        root->left = tmp1;
        root->right = tmp2;
        heap.push(root);
    }
    return heap.top();
}

void deleteHuffmanTree(node *t)
{
    if (t == NULL)
        return;
    deleteHuffmanTree(t->left);
    deleteHuffmanTree(t->right);
    free(t);
}


