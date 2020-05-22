#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <queue>
#include <time.h>
using namespace std;

//元素到桶的索引
map<int, int> numToBucket;
//桶到元素的索引
map<int, int> bucketToNum;
//空桶列表
queue<int> emptyBucket;
//计数桶
int bucket[510000];
int n, k;

//初始化，包括读入数据规模与初始化空桶列表
void init(FILE *&evalIn){
    int x;
    fscanf(evalIn, "N=%d\n", &n);
    fscanf(evalIn, "k=%d\n", &k);
    for(int i = 1; i < k; i++)
        emptyBucket.push(i);
}   

//在线读入数据，俄罗斯方块（MG算法）主过程
void work(FILE *&dataStream){
    int x, b;
    for(int i = 0; i < n; i++){
        fscanf(dataStream, "%d", &x);
        if(numToBucket.find(x) != numToBucket.end() && (b = numToBucket[x]) != 0){
            bucket[b]++;
        }else{
            if(emptyBucket.empty()){
                for(int j = 1; j < k; j++){
                    bucket[j] --;
                    if(bucket[j] == 0){
                        b = j;
                        x = bucketToNum[b];
                        numToBucket[x] = 0;
                        bucketToNum[b] = 0;
                        emptyBucket.push(b);
                    }
                }
            }else{
                b = emptyBucket.front();
                emptyBucket.pop();
                numToBucket[x] = b;
                bucketToNum[b] = x;
                bucket[b] ++;
            }
        }
    }
}

//根据元素在桶中的出现情况估计其在数据流中的出现频数
void eval(FILE *&evalIn, FILE *&out){
    int x, b;
    while(fscanf(evalIn, "%d", &x) != EOF){
        if(numToBucket.find(x) != numToBucket.end() && (b = numToBucket[x]) != 0){
            fprintf(out, "%d\n",bucket[b]);
        }else{
            fprintf(out, "0\n");
        }
    }
}

int main(int argc, char **argv){
    FILE *evalIn = fopen(argv[1], "r");
    FILE *dataStream = fopen(argv[2], "r");
    FILE *out = fopen(argv[3], "w");
    init(evalIn);
    work(dataStream);
    eval(evalIn, out);
    fprintf(stderr, "time: %.2lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}