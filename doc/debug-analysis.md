# 调试分析报告

## 调试过程中遇到的问题

频率溢出
```c++
-        BYTE temp;
-        int sta = fread(&temp,sizeof(BYTE),1,fin->in);
-        if (sta != -1)
-            freq[temp]++;
+        if (freq[buf[i]] != 0xffU)
+            freq[buf[i]]++;
```

指针域没有清零
```c++
node *getNode(BYTE c, long long freq)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->freq = freq;
    temp->val = c;
+   temp->left=NULL;
+   temp->right=NULL;
    return temp;
}
```

## 设计回顾

时空分析  

|function|T()|S()|
|-|-|-|
|getNode|O(1)|O(1)|
|getHuffmanTree|O(n)|O(2n)|
|deleteHuffmanTree|O(2n)|O(n)|
|getEncoding|O(2n)|O(n)|
|getOutputFile|O(1)|O(1)|
|getInputFile|O(1)|O(1)|
|flushW|O(1)|O(1)|
|fileWrite|O(length(bitString))|O(length(bitString))|
|compress|O(length(file))|O(4kb)|
|extract|O(length(file))|O(1kb)|

可以利用多线程同时对文件不同部分进行解压和压缩操作
