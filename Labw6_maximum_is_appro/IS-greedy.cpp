#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include<list>
using namespace std;

int n, ans;
//过滤数组，用于对输入数据去重
bool filt[2510000];
//存储图的邻接表
vector<int> e[2510000];
//记录图中所有节点的实时度数
int deg[2510000];
//记录当前图点的最小度数
int currentMinDeg = 1e9;
//对每个度数建立一个链表，存放所有该度数的点
list< int > degList[2510000];
//存放每个点在链表中的迭代器
list< int >::iterator idit[2510000];

//初始化函数，包括读入，对数据去重
void init(FILE *&in){
    int x, y;
    vector<int>tmp;
    fscanf(in, "%d", &n);
    while(fscanf(in, "%d %d", &x, &y) != EOF){
        e[x].push_back(y);
        e[y].push_back(x);
    }
    memset(filt, 0, sizeof(bool) * n);
    for(int i = 0; i < n; i++){
        tmp.clear();
        for(auto j : e[i])
            if(filt[j] == false){
                filt[j] = true;
                tmp.push_back(j);
            }
        e[i] = tmp;
        for(auto j : e[i])
            filt[j] = false;
    }
}

//构建函数，用于根据度数对点构建链表，并存储他们对应的迭代器
void construct(){
    for(int i = 0; i < n; i++){
        deg[i] = e[i].size();
        degList[deg[i]].push_back(i);
        currentMinDeg = min(currentMinDeg, deg[i]);
    }
    for(int i = 0; i < n; i++)
        for(list<int>::iterator it = degList[i].begin(); it != degList[i].end(); it++)
            idit[*it] = it;
    
    int tmp = 0;
    /*
    for(auto i = degOrd.begin(); i != degOrd.end(); i++){
        fprintf(out, "%d: ", i == degit[tmp++]);
        for(auto j : (*i))
            fprintf(out, "%d(%d), ", j, deg[j]);
        fprintf(out, "\n");
    }*/
}

//将某个点删除，并将它的邻居的点的度数-1
void ban(int x){
    auto it = idit[x];
    degList[deg[x]].erase(it);
    deg[x] = -1;
    for(auto i : e[x]){
        if(deg[i] == -1) continue;
        deg[i] --;
        auto it = idit[i];
        degList[deg[i] + 1].erase(it);
        degList[deg[i]].push_back(i);
        it = degList[deg[i]].end();
        idit[i] = --it;
    }
}

//计算函数，贪心主过程
void work(){
    while(1){
        currentMinDeg = max(0, currentMinDeg - 1);
        while(currentMinDeg < n && (degList[currentMinDeg]).empty())
            currentMinDeg ++;
        if(currentMinDeg == n) return;
        int x = degList[currentMinDeg].front();
        ans++;
        ban(x);
        for(auto i : e[x])
            if(deg[i] != -1) 
                ban(i);
    }
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
//    FILE *out = fopen(argv[2], "w");
    double t1 = clock();
    init(in);
    double t2 = clock();
    construct();
    double t3 = clock();
    work();
    fprintf(stderr, "%d\ntime: %.2lf %.2lf %.2lf\n", ans, (t2 - t1) / CLOCKS_PER_SEC, (t3 - t2) / CLOCKS_PER_SEC, (clock() - t3) / CLOCKS_PER_SEC);
    return 0;    
}