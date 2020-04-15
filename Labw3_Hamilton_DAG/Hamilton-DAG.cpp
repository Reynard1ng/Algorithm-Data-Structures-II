#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <time.h>
using namespace std;

//记录连边
vector <vector<int> > r;
//记录入度
vector <int> d;
//记录以该点为结束的最长路的长度
vector <int> len;
//记录以该点为结束的最长路的上一个点
vector <int> pre;
//记录可以进行动态规划的点的等待列表
queue <int> todo;
int n;

//初始化，包括读入
void init(FILE *in);
//计算动态规划，主要工作函数
void work();
//输出最长路方案
void outit(FILE *out, int id);
//判断可行性等任务在主函数中

void outit(FILE *out, int id){
    if(pre[id] == -1){
        fprintf(out, "%d ", id);
        return;
    }outit(out, pre[id]);
    fprintf(out, "%d ", id);
}

void init(FILE *in){
    int x, y;
    fscanf(in, "%d", &n);
    for(int i = 0; i < n; i++){
        vector<int> x;
        r.push_back(x);
        d.push_back(0);
        len.push_back(0);
        pre.push_back(-1);
    }
    while(fscanf(in, "%d %d", &x, &y) != EOF){
        r[x].push_back(y);
        d[y]++;
    }
}

void work(){
    for(int i = 0; i < n; i++)
        if(d[i] == 0)
            todo.push(i);
    while(!todo.empty()){
        int x = todo.front();
        todo.pop();
        for(int i = 0; i < r[x].size(); i++){
            int y = r[x][i];
            if(len[x] + 1 > len[y]){
                len[y] = len[x]+1;
                pre[y] = x;
            }
            d[y]--;
//            fprintf(stderr, "%d %d\n", y, d[y]);
            if(d[y] == 0)
                todo.push(y);
        }
    }
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    init(in);
    int beginTime = clock();
    work();
    
    int maxn = 0, maxlen = 0;
    for(int i = 0; i < n; i++)
        if(maxlen < len[i]){
            maxlen = len[i];
            maxn = i;
        }
//    fprintf(stderr, "%d %d\n", maxn, maxlen);
    if(maxlen == n - 1){
        fprintf(out, "1\n");
        outit(out, maxn);
    }else
        fprintf(out, "0\n");
    fprintf(stderr, "%.4lfs\n",(clock() - beginTime) * 1.0 / CLOCKS_PER_SEC);
    return 0;
}