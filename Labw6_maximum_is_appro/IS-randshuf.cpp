#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

//算法是线性的，用这个式子可以大体控制程序运行时间
#define DEFAULT(x) (2500000/x)
//记录图的邻接表
vector<int> e[2510000];
//点的随机序列
int ind[2510000];
//被标记无法加入独立集的点
bool ban[2510000];

int n, ans;

//标记某个点的邻居被删除
void Ban(int x){
    for(auto i: e[x])
        ban[i] = 1;
}

//计算函数，包括随机序列，并将序列中的点按顺序尽可能加入独立集
void work(){
    int tans = 0;
    memset(ban, 0, sizeof(bool) * n);
    random_shuffle(ind, ind + n);
    for(int i = 0; i < n; i++){
        if(ban[ind[i]] == 0){
            tans ++;
            ban[ind[i]] = 1;
            Ban(ind[i]);
        }
    }
    ans = max(ans, tans);
}

//主函数，包括读入，和重复多次调用计算函数寻找更优的答案
int main(int argc, char **argv) {
    int x, y;
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    fscanf(in, "%d", &n);
    while(fscanf(in, "%d %d", &x, &y) != EOF){
        e[x].push_back(y);
        e[y].push_back(x);
    }
    double begin = clock();
    for(int i = 0; i < n; i++)
        ind[i] = i;
    for(int i = 0; i < DEFAULT(n); i++)
        work();
    printf("%d\n", ans);
    printf("time: %.2lf\n",(clock() - begin) / CLOCKS_PER_SEC);
    return 0;
}