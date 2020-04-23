#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stdlib.h>
#include<queue>
#include<time.h>
using namespace std;

//存储图，二维数组记录每个点相邻的点
vector<vector<int> >edge;
vector<int> emptyVector;
//二分图分部
vector<int> part[2];
//每个点属于哪个分部
int col[11000];
//每个点的匹配点，若该点为非匹配点置-1
int conn[11000];
//用于匈牙利算法中记录每个点是否尝试增广过
int vis[11000];
//记录独立集
int inSet[11000];
//记录该点在独立集内，但未删除与之有连边的点，将要删除。
queue<int> todo;
int n, m, ans;

void init(FILE *&in){
    int x, y;
    for(int i = 0; i < n; i++)
        edge.push_back(emptyVector);
    memset(col, -1, sizeof(col));
    memset(conn, -1, sizeof(conn));
    memset(inSet, -1, sizeof(inSet));
    for(int i = 0; i < m; i++){
        fscanf(in ,"%d %d", &x, &y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
}

void splitGraph(int u, int c){
    col[u] = c;
    part[c].push_back(u);
    for(auto i : edge[u])
        if(col[i] == -1) splitGraph(i, 1-c);
}

int find(int x){
    for(auto i : edge[x]){
        if(vis[i]) continue;
        vis[i] = 1;
        if(conn[i] == -1 || find(conn[i])){
            conn[i] = x;
            conn[x] = i;
            return 1;
        }
    }return 0;
}

void workSet(){
    for(int i = 0; i < n; i++)
        if(conn[i] == -1)
            todo.push(i);
    while(!todo.empty()){
        int x = todo.front();
        todo.pop();
        inSet[x] = 1;
        for(auto i : edge[x]){
            if(inSet[i] != -1) continue;
            inSet[i] = 0;
            if(inSet[conn[i]] != -1) continue;
            todo.push(conn[i]);
        }
    }
    for(int i = 0; i < n; i++){
        if(inSet[i] == -1)
            inSet[i] = col[i];
    }
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    fscanf(in, "%d %d", &n, &m);
    ans = n;
    init(in);
    int beginTime = clock();
    for(int i = 0; i < n; i++)
        if(col[i] == -1)
            splitGraph(i, 0);
    for(auto i: part[0]){
        memset(vis, 0, sizeof(vis));
        if(find(i)) ans--;
    }workSet();
    fprintf(out, "%d\n", ans);
    for(int i = 0; i < n; i++){
        if(inSet[i])
            fprintf(out, "%d\n", i);
    }
    fprintf(stderr, "ans:%d time:%.2lfs\n", ans, 1.0*(clock() - beginTime)/CLOCKS_PER_SEC);
    return 0;
}