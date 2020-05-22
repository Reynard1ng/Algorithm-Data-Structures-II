# 第8周上机实验

数据结构与算法II,2020春
丁海鹏,2018202045,2020-5-22


## Tested Environment
- macOS Catalina 10.15.4
- Apple clang version 11.0.3 (clang-1103.0.32.29)


## Compile the code:
g++  MisraGries.cpp -o MG -O2


## Parameters:
- please input 3 file directions in order
- in.txt data.txt out.txt 
- any illegal input may cause unpredictable errors


## Run:
We use the default file names as the example (retrieved from OBE):

./W in_433.txt data_433_10.txt eval_433.txt

This program use MisraGries sampling to evaluate the number of particular elements' existence in the data stream. It's not accurate, but the error won't exceed $N/k$.

You just need to check if the answer is reasonable.

