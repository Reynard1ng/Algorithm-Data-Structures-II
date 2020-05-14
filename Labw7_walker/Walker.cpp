#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <time.h>
using namespace std;

#define MAX_NUM 23333
const double eps = 1e-10;

int n, q;

//元素键值
double key[MAX_NUM];
//元素权值
double val[MAX_NUM];
//元素初始权值和，用于缩放。
double sumVal;

//队列，分别存放缩放后权值 <1 和 >=1 的元素
queue < pair<int, double> > tiny, huge;
//红酒杯分层界面
double cupBound[MAX_NUM];
//红酒杯中两层对应元素的索引
int cupInd[MAX_NUM][2];


int randInN(int n){
    while(1){
        int t = rand();
        if(t != 0 && t <= RAND_MAX / n * n)
            return (t - 1) % n; 
    }
}

double randIn1(){
    return 1.0 * rand() / RAND_MAX;
}

double fabs(double x){
    return x > 0 ? x : -x;
}

//初始化，读入元素并缩放权值
void init(FILE *&in){
    fscanf(in, "%d %d", &n, &q);
    for(int i = 0; i < n; i++){
        fscanf(in, "%lf %lf", &key[i], &val[i]);
        sumVal += val[i];
    }
    for(int i = 0; i < n; i++){
        val[i] = val[i] / sumVal * n;
        if(val[i] >= 1) huge.push(make_pair(i, val[i]));
        else tiny.push(make_pair(i, val[i]));
    }
}

//调酒，将元素分配到n个红酒杯中
void buildCup(){
    for(int i = 0; i < n - 1; i++){
        pair<int, double> smaller = tiny.front();
        pair<int, double> greater = huge.front();
        tiny.pop(); 
        huge.pop();
        cupInd[i][0] = smaller.first;
        cupInd[i][1] = greater.first;
        cupBound[i] = smaller.second;
        greater.second -= 1 - smaller.second;
        if(greater.second >= 1 - eps)
            huge.push(greater);
        else tiny.push(greater); 
    }
    pair<int, double> left = huge.front();
    cupInd[n - 1][0] = cupInd[n - 1][1] = left.first;
    cupBound[n - 1] = 1;
}

//生成所要求数量的抽样
void sampling(FILE *&out){
    while(q--){
        int i = randInN(n);
        double j = randIn1();
        fprintf(out, "%.0lf\n", key[cupInd[i][j >= cupBound[i] ? 1 : 0]]);
    }
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    init(in);
    buildCup();
    sampling(out);
    fprintf(stderr, "time: %.2lf\n", 1.0*clock()/CLOCKS_PER_SEC);
    return 0;
}