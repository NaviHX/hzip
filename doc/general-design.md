# 概要设计

功能一思路: 首先向文件中写入校验字,抽样前4k字符统计频率,构建出哈夫曼树,获取编码表,将频率写入文件,依次将每个字符转换后写入到文件中  

功能二思路: 首先检查文件校验字,从文件中获取频率表,构建哈夫曼树,依次读入比特,从哈夫曼树上获得实际的字符

## 压缩文件结构

```
0x0 - 0x3 :'h','z','i','p'
0x4 : remainder 标记最后一个字节实际用到的比特数
0x4 后256字节 : 频率表
```

## 数据结构定义

```c++
struct node
{
    node *left;     //左子节点
    node *right;    //右子节点
    long long freq; //频率
    BYTE val;       //权值
};
```

## 主程序流程

```c++
int main(int argc, char **argv)
{
    if (argc == 1) //无参数
        //输出帮助信息
    else //处理参数
    {
        int flag = 0;
        string path = "";
        string opath = "";
        for (int i = 1; i < argc; i++)
        {
            string arg(argv[i]);
            if (arg == "-h" || arg == "--help")
            {
                //输出帮助信息
            }
            else if (arg == "-c" || arg == "--compress")
                flag = 0;
            else if (arg == "-e" || arg == "--extract")
                flag = 1;
            else if(arg=="-o")
            {
                //保存输出路径
            }
            else if (arg[0] != '-')
                //保存输入路径
        }
        if(path=="")
        {
            cout<<"Path Needed\n";
            return 0;
        }
        if (flag == 0)
        {
            if(opath=="")
                opath = path + ".hzp";
            compress(const_cast<char*>(path.c_str()), const_cast<char*>(opath.c_str()));
        }
        else if (flag == 1)
        {
            if(opath=="")
                opath = path + ".ext";
            extract(const_cast<char*>(path.c_str()), const_cast<char*>(opath.c_str()));
        }
        cout << "Done" << endl;
    }
```
