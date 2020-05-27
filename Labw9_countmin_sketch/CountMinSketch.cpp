#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>

#define PrimeLim 10000000
#define Dmax 2333
using namespace std;
//预设误差值
const double eps = 0.0001;
//预设概率错误值
const double delta = 0.0001;
//计算得到的hashmap长度和组数
int W, d;
//筛表，记录每个数是否为质数。除0外，每个数0代表是质数，1代表不是
bool isp[PrimeLim + 5];
//记录筛表内的质数
int pri[PrimeLim + 5];
//构建的全域哈希族
int a[Dmax], b[Dmax], p[Dmax];
//哈希表，担任计数工作
vector < vector<int> > counter;

//计算参数，根据预设的参数计算hashmap长度与组数
void calcParas(){
    W = (int)(2.0/eps);
    d = log(1.0/delta) / log(2.0);
}

//筛质数
void primeSieve(){
    for(int i = 2; i < PrimeLim; i++)
        if(!isp[i]){
            pri[++pri[0]] = i;
            for(long long j = 1ll * i * i; j < PrimeLim; j += i)
                isp[j] = 1;
        }
}

//随机生成一个0~n-1的数
int randInN(int n){
    while(1){
        int t = rand();
        if(t != 0 && t <= RAND_MAX / n * n)
            return (t - 1) % n; 
    }
}

//初始化，生成全0哈希表和全域哈希函数
void init(){
    vector <int> tmp(W);
    for(int i = 0; i < d; i++){
        counter.push_back(tmp);
        a[i] = pri[randInN(pri[0]) + 1];
        b[i] = pri[randInN(pri[0]) + 1];
        p[i] = pri[randInN(pri[0]) + 1];
    }
}

//计算元素x在第i个哈希表中的哈希值
int hashid(int x, int i){
    return (1ll * a[i] * x + b[i]) % p[i] % W;
}

//主工作函数，
void work(FILE *&in, FILE *&out){
    int maxid = 0;
    int x, dt;
    while(fscanf(in, "%d %d", &x, &dt)!=EOF){
        maxid = max(maxid, x);
        for(int i = 0; i < d; i++)
            counter[i][hashid(x, i)] += dt;
    }
    for(int i = 0; i <= maxid; i++){
        int ans = 1 << 30;
        for(int j = 0; j < d; j++)
            ans = min(ans, counter[j][hashid(i, j)]);
        fprintf(out, "%d %d\n", i, ans);
    }
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    calcParas();
    primeSieve();
    init();
    work(in, out);
    fprintf(stderr, "time:%.2lf\n", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}