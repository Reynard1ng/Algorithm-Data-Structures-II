# 第10周上机实验

数据结构与算法II,2020春
丁海鹏,2018202045,2020-6-11


## Tested Environment
- macOS Catalina 10.15.4
- Apple clang version 11.0.3 (clang-1103.0.32.29)


## Compile the code:
make
please refer to makefile for details


## Parameters:
- please input 1 number ans 4 file directions in order
- **number_of_strings_in_stream_data.txt** data.txt query.txt out.txt answer.txt 
- any illegal input may cause unpredictable errors


## Run:
We use the default file names as the example (retrieved from OBE):

./bt 100 f100.txt q100.txt o100.txt a100.txt

This program use bloom filter to determine if the strings in `query.txt` exist in  `data.txt` within $O(n)$ bits memory.

The ratio of false positive is related to the memory parameter in function `calcParas()`.

You just need to check if the answer is reasonable.

## Instructions

special thanks to: https://github.com/ljhnhlh/MD5