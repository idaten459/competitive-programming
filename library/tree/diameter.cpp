/*
 木構造の直径を求める
 頂点数をとして、計算量はO(n)
*/

#include<bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>>& p, vector<int>& d,int pos,int dis=0){
    d[pos]=dis;
    REP(i,p[pos].size()){
        int to = p[pos][i];
        if(d[to]==INT_MAX){
            dfs(p,d,to,dis+1);
        }
    }
}

int diam(vector<vector<int>>& p,int n){
    int res;
    vector<int> d(n,INT_MAX);
    dfs(p,d,0);
    int maxd = *max_element(all(d));
    auto itr = find(all(d),maxd);
    int index = itr-d.begin();
    vector<int> d2(n,INT_MAX);
    dfs(p,d2,index);
    res = *max_element(all(d2));
    return res;
}
