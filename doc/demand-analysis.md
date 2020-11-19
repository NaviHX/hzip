# 需求分析

任务: 利用哈夫曼编码压缩,解压文件

功能一:  压缩文件  
输入: hzip -c test.in -o test.hzp  
输出: 产生一个`test.hzp`文件,其为经过压缩后的文件  

功能二: 解压文件  
输入: hzip -e test.hzp -o test.out  
输出: 产生一个`test.out`文件,其为解压后的文件.如果该文件格式不是压缩文件,会输出`not a hzip file`  
