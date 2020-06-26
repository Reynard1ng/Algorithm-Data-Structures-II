#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<map>
using namespace std;

#define DOCS 40000
#define WORDS 30000
#define MAXM 400
const double s = 0.8;
const double eps = 0.3;
const double delta = 0.3;

//文档数量，词库数量
int docs, words;
//LSH 中参数 M,b,r
int M, b, r;
//用于记录文档中包含的单词
map <int,int> dataset[DOCS];
//用于临时存放随机生成的排列
int perm[WORDS];
//存储文档签名
int sign[DOCS][MAXM];

double fabs(double x){
    return x>0?x:-x;
}

//计算 LSH 的参数 M=56,b=7,r=8
void calcParas(){
    M = (int) (3*s/eps/eps*log(2/delta)+1);
    double bests = 0;
    for(int i = 1; i <= M; i++){
        int tmpb = i;
        int tmpr = (M-1)/tmpb+1;
        double tmps = pow(1.0/tmpb, 1.0/tmpr);
        cerr << tmps << ' ' << tmpb << ' ' << tmpr << endl;
        if(fabs(tmps - s) < fabs(bests - s)){
            bests = tmps;
            b = tmpb;
            r = tmpr;
        }
    }M = b*r;
    cerr << M << b << r << endl;
}

//加载数据
void loadData(FILE *in){
    int tmpd, tmpw;
    fscanf(in, "%d", &docs);
    fscanf(in, "%d", &words);
    fscanf(in, "%*d");
    while(fscanf(in, "%d %d %*d", &tmpd, &tmpw) != EOF)
        dataset[tmpd][tmpw] = 1;
}

//minHashing 生成文档签名，并将排列和签名输出至临时文件
void minHashing(FILE *signout){
    fprintf(signout, "%d %d %d %d %d\n", docs, words, M, b, r);
    for(int i = 1; i <= words; i++)
        perm[i] = i;
    for(int i = 1; i <= M; i++){
        fprintf(stderr, "%d/%d finished\n", i, M);
        random_shuffle(perm+1, perm+words+1);
        for(int j = 1; j <= words; j++)
            fprintf(signout, "%d ", perm[j]);
        fprintf(signout, "\n");
        for(int j = 1; j <= docs; j++)
            for(int k = 1; k <= words; k++)
                if(dataset[j].find(perm[k]) != dataset[j].end()){
                    sign[j][i] = perm[k];
                    break;
                }
    }
    for(int i = 1; i <= docs; i++){
        for(int j = 1; j <= M; j++)
            fprintf(signout, "%d ", sign[i][j]);
        fprintf(signout, "\n");
    }
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *signout = fopen(argv[2], "w");
    calcParas();
    loadData(in); 
    minHashing(signout);
    return 0;   
}