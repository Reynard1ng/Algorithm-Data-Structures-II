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
const double eps = 0.1;
//预设概率错误值
const double delta = 0.1;
//计算得到的hashmap长度和组数
int W, d;
//筛表，记录每个数是否为质数。除0外，每个数0代表是质数，1代表不是
bool isp[PrimeLim + 5];
//记录筛表内的质数
int pri[PrimeLim + 5];
//构建的全域哈希族
int ha[Dmax], hb[Dmax], hp[Dmax];
int ga[Dmax], gb[Dmax], gp[Dmax];
//哈希表，担任计数工作
vector < vector<int> > counter;

//计算参数，根据预设的参数计算hashmap长度与组数
void calcParas(){
    W = (int)(3.0/eps/eps);
    d = (int)(16 * log(2.0/delta));
}

//筛质数
void primeSieve(){
    for(int i = 2; i < PrimeLim; i++)
        if(!isp[i]){
            if(i >= 1000000) 
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
        ha[i] = pri[randInN(pri[0]) + 1];
        hb[i] = pri[randInN(pri[0]) + 1];
        hp[i] = pri[randInN(pri[0]) + 1];
        ga[i] = pri[randInN(pri[0]) + 1];
        gb[i] = pri[randInN(pri[0]) + 1];
        gp[i] = pri[randInN(pri[0]) + 1];
    }
}

int hash_h(int i, int x){
    return (1ll * ha[i] * x + hb[i]) % hp[i] % W;
}

int hash_g(int i, int x){
    return (1ll * ga[i] * x + gb[i]) % gp[i] % 2 * 2 - 1;
}

void work(FILE *in, FILE *out){
    int m = 0;
    int x, delta;
    while(fscanf(in, "%d %d", &x, &delta) != EOF){
        m = max(x, m);
        for(int i = 0; i < d; i++){
            int h = hash_h(i, x); 
            int g = hash_g(i, x);
            counter[i][h] += delta * g;
        }
    }
    vector<int>tmp;
    for(int i = 0; i <= m; i++){
        tmp.clear();
        for(int j = 0; j < d; j++){
            int h = hash_h(j, i);
            int g = hash_g(j, i);
            tmp.push_back(g * counter[j][h]);
        }sort(tmp.begin(), tmp.end());
        int mid = d/2;
        if(d % 2 == 0){
            fprintf(out, "%d %d\n", i, (tmp[mid - 1] + tmp[mid]) / 2);
        }else{
            fprintf(out, "%d %d\n", i, tmp[mid]);
        }
    }
    
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    calcParas();
    primeSieve();
    
    cerr << W << ' ' << d << endl;
    init();
    work(in, out);
    fprintf(stderr, "time:%.2lf\n", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}