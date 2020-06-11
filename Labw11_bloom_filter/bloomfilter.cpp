#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <bitset>
#include "MD5.hpp"
using namespace std;

#define MAXBITS 144500

const int BUF_MAX=2010;
//数据读取缓冲区
char buf[BUF_MAX];
//布隆过滤器主体
bitset <MAXBITS> filter;
//数据数量，布隆过滤器用到的bits数量和哈希函数数量
int n, m, k;

//初始化函数，计算参数
void calcParas(){
    m = (int)(14.4 * n);
    k = log(2) * m / n;
}

//读入数据流
void Loaddata(FILE *data){
    while(fgets(buf, BUF_MAX - 10, data) != NULL){
        string tmp(buf);
        unsigned int receiver;
        for(int i = 0; i < k; i++){
            MD5 tmphash;
            tmphash.read(tmp);
            receiver = tmphash.Encryption() % m;
            filter.set(receiver, true);
            tmp += " ";
        }
    }
}

//判断数据流中的字符串是否出现过，并计算 false positive 率
void Checkdata(FILE *query, FILE *out, FILE *answer){
    int absense = 0, fault = 0;
    while(fgets(buf, BUF_MAX - 10, query) != NULL){
        int flag = 1;
        string tmp(buf);
        unsigned int receiver;
        for(int i = 0; i < k; i++){
            MD5 tmphash;
            tmphash.read(tmp);
            receiver = tmphash.Encryption() % m;
            flag &= filter[receiver];
            tmp += " ";
        }
        int trueflag;
        fprintf(out, "%d\n", flag);
        fscanf(answer, "%d", &trueflag);
        if(trueflag == 0){
            absense++;
            if(trueflag != flag)
                fault++;
        }else
            if(trueflag != flag){
                cerr << "extreme serious fault happens!" << endl;
                exit(0);
            }
    }
    cerr << "false positive: " << 1.0 * fault / absense <<endl;
}

int main(int argc, char **argv){
    n = stoi(argv[1], 0, 10);
    FILE *data = fopen(argv[2], "r");
    FILE *query = fopen(argv[3], "r");
    FILE *out = fopen(argv[4], "w");
    FILE *answer = fopen(argv[5], "r");
    calcParas();
    Loaddata(data);
    Checkdata(query, out, answer);
    return 0;
}