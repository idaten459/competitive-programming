/*
 2部グラフの判定
 dfsがtrueを返したら、2部グラフ
 計算量は、O(m)?
 利用例は、
 https://atcoder.jp/contests/code-festival-2017-qualb/submissions/8006141
*/

class Bipartite{
public:
    vector<vector<int>> path;
    vector<int> res;
    Bipartite(int n,vector<vector<int>> &path):path(path){
        res.resize(n);
        fill(all(res),-1);
    }
    
    bool judge(){
        return dfs(this->path,this->res,0,0);
    }
    bool dfs(vector<vector<int>>& path,vector<int>&res,int now,int color){
        res[now]=color;
        REP(i,path[now].size()){
            int next=path[now][i];
            if(res[next]==color){
                return false;
            }
            if(res[next]==-1&&!dfs(path,res,next,1-color)){
                return false;
            }
        }
        return true;
    }
};

int main(){
    int n,m;
    cin >> n >> m;
    vector<int> a(m);
    vector<int> b(m);
    vector<vector<int>> path(n);
    REP(i,m){
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
        path[a[i]].push_back(b[i]);
        path[b[i]].push_back(a[i]);
    }
    Bipartite bp(n, path);
    if(bp.judge()){
        int cw=0,cb=0;
        REP(i,n){
            if(bp.res[i]==0){
                cw++;
            }else if(bp.res[i]==1){
                cb++;
            }
        }
        put((ll)cw*cb-m);
    }else{
        put((ll)n*(n-1)/2-m);
    }
    return 0;
}
