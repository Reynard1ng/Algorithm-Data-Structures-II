#include<stdio.h>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstdlib>
#include<unistd.h>
#include<fstream>
#include<time.h>
using namespace std;

class Node{
    public:
        int val, col;
        Node *ch[2], *p;
        Node(){};
        Node(int _val, int _col, Node *_left, Node *_right, Node *_p):
            val(_val), col(_col), p(_p){
                ch[0] = _left, ch[1] = _right;
            };
};

class RedBlackTree{
    private:
        Node *nil;
        Node *root;
        void rotate(Node *x, int dir){
            int rdir = dir ^ 1;
            Node *y = x->ch[rdir];
            x -> ch[rdir] = y -> ch[dir];
            if(y -> ch[dir] != nil)
                y -> ch[dir] -> p = x;
            y -> p = x -> p;
            if(x -> p == nil)
                root = y;
            else if(x == x -> p -> ch[dir])
                x -> p -> ch[dir] = y;
            else x -> p -> ch[rdir] = y;
            y -> ch[dir] = x;
            x -> p = y;
        }
        void insertFixup(Node *z){
            Node *y;
            int dir;
            while(z -> p -> col == 0){
                if(z -> p == z -> p -> p -> ch[0]) dir = 0;
                else dir = 1;
                int rdir = dir ^ 1;
                y = z -> p -> p -> ch[rdir];
                if(y -> col == 0){
                    z -> p -> col = 1;
                    y -> col = 1;
                    z -> p -> p -> col = 0;
                    z = z -> p -> p;
                }else{
                    if(z == z -> p -> ch[rdir]){
                        z = z -> p;
                        rotate(z, dir);
                    }
                    z -> p -> col = 1;
                    z -> p -> p -> col = 0;
                    rotate(z -> p -> p, rdir);
                }
            }root -> col = 1;
        }
        void clearTree(Node *x){
            if(x == nil) return;
            clearTree(x -> ch[0]);
            clearTree(x -> ch[1]);
            delete x;
        }
    public:
        RedBlackTree(){
            nil = new Node(-1, 1, 0, 0, 0);
            nil -> ch[0] = nil;
            nil -> ch[1] = nil;
            nil -> p = nil;
            root = 0;
        }
        Node * newnode(int _val){
            return new Node(_val, 1, nil, nil, nil);
        }
        void insert(Node *z){
            if(root == 0) {root = z; return;}
            Node *y = nil;
            Node *x = root;
            while(x != nil){
                y = x;
                if(z -> val < x -> val)
                    x = x -> ch[0];
                else x = x -> ch[1];
            }
            z -> p = y;
            if(y == nil)
                root = z;
            else if(z -> val < y -> val)
                y -> ch[0] = z;
            else y -> ch[1] = z;
            z -> ch[0] = z -> ch[1] = nil;
            z -> col = 0;
            insertFixup(z);
        }
        bool find(int val){
            if(root == 0) return false;
            Node *current = root;
            while(current != nil){
                if(current -> val == val) 
                    return true;
                if(current -> val < val) 
                    current = current -> ch[1];
                else 
                    current = current -> ch[0];
            }return false;
        }
        void accessAll(vector<int> &res){
            if(root == 0) return;
            queue<Node *>Q;
            Q.push(root);
            while(!Q.empty()){
                Node *current = Q.front();
                Q.pop();
                res.push_back(current -> val);
                if(current -> ch[0] != nil)
                    Q.push(current -> ch[0]);
                if(current -> ch[1] != nil)
                    Q.push(current -> ch[1]);
                    
            }
        }
        void clear(){
            if(root == 0) return;
            clearTree(root);
            root = 0;
        }
};

vector<RedBlackTree> graph;
int N;

void addr(int x, int y){
    graph[x].insert(graph[x].newnode(y));
}

void loadData(FILE* in){
    int x, y;
    fscanf(in, "%d", &N);
    while(graph.size() <= N){
        RedBlackTree tmp;
        graph.push_back(tmp);
    }
    while(fscanf(in, "%d %d",&x ,&y)!=EOF){
        addr(x, y); addr(y, x);
    }
}

void solve1(FILE* in, FILE* out){
    int x,y;
    while(fscanf(in, "%d %d", &x, &y)!=EOF)
        fprintf(out, "%d\n", graph[x].find(y)?1:0);
}

void solve2(FILE* in, FILE* out){
    int x,y;
    vector<int>res, tmpx, tmpy, ans;
    while(res.size() <= N) 
        res.push_back(0);
    while(fscanf(in, "%d %d", &x, &y)!=EOF){
        fprintf(out, "%d %d \n", x, y);
        if(!graph[x].find(y)) 
            continue;
        tmpx.clear();
        tmpy.clear();
        ans.clear();
        graph[x].accessAll(tmpx);
        graph[y].accessAll(tmpy);
        for(int i = 0; i < tmpx.size(); i++)
            res[tmpx[i]]++;
        for(int i = 0; i < tmpy.size(); i++)
            if(res[tmpy[i]] == 1)
                ans.push_back(tmpy[i]);
        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); i++)
            fprintf(out, "%d\n", ans[i]);
        for(int i = 0; i < tmpx.size(); i++)
            res[tmpx[i]]--;
    }
}

int main(int argc, char **argv){
    FILE* dataIn = fopen(argv[1], "r");
    // cerr << argv[1] << endl;
    int preTimeB = clock();
    loadData(dataIn);
    int preTimeE = clock();
    FILE* prob1 = fopen(argv[2], "r");
    FILE* ans1 = fopen(argv[3], "w");
    // cerr << argv[2] << "\n" << argv[3] << endl;
    int prob1TimeB = clock();
    solve1(prob1, ans1);
    int prob1TimeE = clock();
    FILE* prob2 = fopen(argv[4], "r");
    FILE* ans2 = fopen(argv[5], "w");
    // cerr << argv[4] << "\n" << argv[5] << endl;
    int prob2TimeB = clock();
    solve2(prob2, ans2);
    int prob2TimeE = clock();
    fprintf(stderr, "Loading Time Consumption: %.2lf ms\n", 1.0 * (preTimeE - preTimeB) / CLOCKS_PER_SEC * 1000);
    fprintf(stderr, "Work__1 Time Consumption: %.2lf ms\n", 1.0 * (prob1TimeE - prob1TimeB) / CLOCKS_PER_SEC * 1000);
    fprintf(stderr, "Work__2 Time Consumption: %.2lf ms\n", 1.0 * (prob2TimeE - prob2TimeB) / CLOCKS_PER_SEC * 1000);
    return 0;
}
