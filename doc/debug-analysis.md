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
