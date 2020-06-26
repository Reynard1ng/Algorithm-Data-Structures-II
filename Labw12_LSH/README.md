# 第12周上机实验

数据结构与算法II,2020春
丁海鹏,2018202045,2020-6-26


## Tested Environment
- macOS Catalina 10.15.4
- Apple clang version 11.0.3 (clang-1103.0.32.29)


## Compile the code:
g++ sign.cpp -o sign

g++ LSH.cpp -o LSH


## Parameters:
- please input the direction of raw data and target modified data as the parameter of excutable file `sign`
- please input the direction of modified data, query file and the answer file as the parameter of excutable file `LSH`


## Run:
We use the default file names as the example (retrieved from OBE):

./sign docword.enron.txt docword.enron.sign

./sign docword.enron.txt query.txt query.ans

This program use LSH to find the similar files in raw data `docword.enron.txt`

The accuracy of the answer is related to the parameter in function `calcParas()` in `sign.cpp`.

You just need to check if the answer is reasonable.

