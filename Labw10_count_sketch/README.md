# 第10周上机实验

数据结构与算法II,2020春
丁海鹏,2018202045,2020-6-4


## Tested Environment
- macOS Catalina 10.15.4
- Apple clang version 11.0.3 (clang-1103.0.32.29)


## Compile the code:
g++  CountSketch.cpp -o CS 


## Parameters:
- please input 2 file directions in order
- data.txt out.txt 
- any illegal input may cause unpredictable errors


## Run:
We use the default file names as the example (retrieved from OBE):

./CS data_100_10.txt out_100.txt

This program use Count-Min Sketch to evaluate the times of each elements' existence in data stream. It can't be, and shouldn't be accurate, in spite that you set the $\varepsilon$ and $\delta$ really small.

You just need to check if the answer is reasonable.

