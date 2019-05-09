/*
 2部グラフの判定
 dfsがtrueを返したら、2部グラフ
 計算量は、O(m)?
 利用例は、
 https://atcoder.jp/contests/code-festival-2017-qualb/submissions/4893383
*/

struct edge{
    int to;
};

int n,m;
vector<vector<edge>> e;
vector<int> c;

bool dfs(int a,int color){
    c[a]=color;
    REP(i,e[a].size()){
        if(c[e[a][i].to]==color){
            return false;
        }
        if(c[e[a][i].to]==-1&&!dfs(e[a][i].to,1-color)){
            return false;
        }
    }
    return true;
}
int main(){
    cin >> n >> m;
    vector<int> a(m);
    vector<int> b(m);
    e.resize(n);
    REP(i,m){
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
        edge ed1;
        ed1.to = b[i];
        e[a[i]].push_back(ed1);
        edge ed2;
        ed2.to = a[i];
        e[b[i]].push_back(ed2);
    }
    c.resize(n);
    fill(all(c),-1);
    if(dfs(a[0],0)){
        int cw=0,cb=0;
        REP(i,n){
            if(c[i]==0){
                cw++;
            }else if(c[i]==1){
                cb++;
            }
        }
        put((ll)cw*cb-m);
    }else{
        put((ll)n*(n-1)/2-m);
    }
    return 0;
}