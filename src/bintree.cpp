#include "bintree.h"
using namespace std;

/*
获取节点
c: 该节点的字符
freq: 该节点的频率
ret-> 结点指针 
*/
node *getNode(BYTE c, long long freq)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->freq = freq;
    temp->val = c;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

/*
获取哈夫曼树
freq[]: 频率表
ret-> 树的根指针
*/
node *getHuffmanTree(BYTE freq[])
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

/*
删除哈夫曼树
t: 待删除的哈夫曼树
*/
void deleteHuffmanTree(node *t)
{
    if (t == NULL)
        return;
    deleteHuffmanTree(t->left);
    deleteHuffmanTree(t->right);
    free(t);
}

/*
获取编码表
encoding: 用于保存编码表的字符串组
root: 当前的节点
state: 从根节点到当前节点的路径产生的比特串
*/
void getEncoding(string *encoding, node *root, vector<char> &state)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            string temp = "";
            for (int i = 0; i < state.size(); i++)
                temp += state[i];
            encoding[root->val] = temp;
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
