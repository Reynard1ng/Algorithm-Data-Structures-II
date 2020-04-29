#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <time.h>

#define MAX_SET 1000
#define MAX_ELE 10000
#define MAX_BUF 100000

//记录每个元素在集合中的状态，使用char类型减小内存占用
char exist[MAX_SET][MAX_ELE];
//记录每个集合剩余有效元素数量
int eff[MAX_SET];
//记录每个集合是否被计入答案
bool mark[MAX_SET];
//对行进行数字解析的缓冲区
char buf[MAX_BUF];
//元素数，子集数量
int n, m;

void init(FILE *&in){
    fgets(buf, MAX_BUF - 5, in);
    sscanf(buf, "%d", &n);
    fgets(buf, MAX_BUF - 5, in);
    sscanf(buf, "%d", &m);
    for(int i = 0; i < m; i++){
        int x, offset = 0, tmpoffset = 0;
        fgets(buf, MAX_BUF - 5, in);
        while(sscanf(buf + offset, "%d%n", &x, &tmpoffset) != EOF){
            offset += tmpoffset;
            exist[i][x] = 1;
            eff[i] ++;
        }
    }
}

int check(){
    int maxn = -1, maxid = -1;
    for(int i = 0; i < m; i++)
        if(eff[i] > maxn){
            maxn = eff[i];
            maxid = i;
        }
    return maxn == 0 ? -1 : maxid;
}

void output(int ans, FILE *&out){
    fprintf(out, "%d\n", ans);
    for(int i = 0; i < m; i++)
        if(mark[i]){
            for(int j = 0; j < n; j++)
                if(exist[i][j] != 0)
                    fprintf(out, "%d ", j);
            fprintf(out ,"\n");
        }
}

void work(FILE *out){
    int ans = 0;
    int cnt = 0;
    int select;
    while((select = check()) != -1){
        mark[select] = 1;
        ans++;
        cnt += eff[select];
        for(int i = 0; i < n; i++){
            if(exist[select][i] == 1)
                for(int j = 0; j < m; j++)
                    if(exist[j][i] == 1){
                        exist[j][i] = 2;
                        eff[j] --;
                    }
        }
    }
    if(cnt != n) fprintf(stderr, "the total set can't be covered");
    else output(ans, out);
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    init(in);
    double begin = clock();
    work(out);
    fprintf(stderr, "%.2lfs\n", (clock() - begin)/CLOCKS_PER_SEC);
    return 0;
}