#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<time.h>
#include<map>
using namespace std;

#define DOCS 40000
#define WORDS 30000
#define MAXM 400
#define MAXB 40
#define MAXR 40
#define PRIMELIM 10000000
const double s = 0.8;
const double eps = 0.3;
const double delta = 0.3;

int docs, words;
int M, b, r;
map <int,int> dataset[DOCS];
//存放生成好的排列
int perm[MAXM][WORDS];
//存放生成好的文档签名
int sign[DOCS][MAXM];
//筛质数
int isp[PRIMELIM], pri[PRIMELIM];
//将签名哈希至桶中的哈希参数
int hasha[MAXB], hashp[MAXB]; 
//被哈希进桶的band所对应的文档
vector<int>bucket[MAXB][DOCS];
//询问文档的单词集
map<int,int> queryset;
//询问文档的签名
int querysign[MAXM];
//与询问文档匹配的答案集合
vector <int> answerset;

//筛质数
void primeSieve(){
    for(int i = 2; i <= PRIMELIM; i++)
        if(isp[i] == 0){
            pri[++pri[0]] = i;
            for(long long j = 1ll * i * i; j <= PRIMELIM; j += i)
                isp[j] = 1;
        }
}

//读取由 sign.cpp 生成的数据
void loadData(FILE *in){
    fscanf(in, "%d %d %d %d %d", &docs, &words, &M, &b, &r);
    for(int i = 1; i <= M; i++)
        for(int j = 1; j <= words; j++)
            fscanf(in, "%d", &perm[i][j]);
    for(int i = 1; i <= docs; i++)
        for(int j = 1; j <= M; j++)
            fscanf(in, "%d", &sign[i][j]);
}

//对文档集合签名计算其被哈希的位置。
void LSH(){
    for(int i = 1; i <= b; i++){
        hasha[i] = pri[rand()%pri[0]+1];
        hashp[i] = pri[rand()%pri[0]+1];
    }for(int i = 1; i <= docs; i++){
        for(int j = 1; j <= b; j++){
            int tmpf = 0;
            for(int k = (j-1)*r+1; k <= j*r; k++)
                tmpf = (1ll * tmpf * hasha[j] + sign[i][k]) % hashp[j];
            tmpf %= docs;
            bucket[j][tmpf].push_back(i);
        }
    }
}

//读入询问文档，将答案输出
void work(FILE *query, FILE* ans){
    int tmpw, tmpc;
    while(fscanf(query, "%d %d", &tmpw, &tmpc) != EOF)
        queryset[tmpw] = 1;
    //生成询问文档签名
    for(int i = 1; i <= M; i++)
        for(int j = 1; j <= WORDS; j++)
            if(queryset.find(perm[i][j]) != queryset.end()){
                querysign[i] = perm[i][j];
                break;
            }
    //生成询问文档被哈希进桶中的位置
    for(int i = 1; i <= b; i++){
        int tmpf = 0;
        for(int j = (i-1)*r+1; j <= i*r; j++)
            tmpf = (1ll * tmpf * hasha[i] + querysign[j]) % hashp[i];
        tmpf %= docs;
        //比对哈希冲突的文档是否完全一致
        for(auto v: bucket[i][tmpf]){
            int flag = 0;
            for(int j = (i-1)*r+1; j <= i*r; j++)
                if(sign[v][j] != querysign[j]){
                    flag = 1;
                    break;
                }
            if(!flag) answerset.push_back(v);
        }
    }
    //去重，输出答案
    sort(answerset.begin(), answerset.end());
    if(answerset.size() == 0){
        fprintf(ans, "no match docs.");
        return;
    }
    fprintf(ans, "%d ", answerset[0]);
    for(int i = 1; i < answerset.size(); i++)
        if(answerset[i] != answerset[i - 1])
            fprintf(ans, "%d ", answerset[i]);
}

int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r");
    FILE *query = fopen(argv[2], "r");
    FILE *ans = fopen(argv[3], "w");
    primeSieve();
    loadData(in);
    LSH();
    int begin = clock();
    work(query, ans);
    cerr << "time consumption: " << 1.0*(clock() - begin) / CLOCKS_PER_SEC << "s" <<endl;
    return 0;
}