#include "bits/stdc++.h"
using namespace std;
#define Rep(i,n) for(int i=0;i<(int)(n);i++)
#define For(i,n1,n2) for(int i=(int)(n1);i<(int)(n2);i++)
#define REP(i,n) for(ll i=0;i<(ll)(n);i++)
#define RREP(i,n) for(ll i=((ll)(n)-1);i>=0;i--)
#define FOR(i,n1,n2) for(ll i=(ll)(n1);i<(ll)(n2);i++)
#define put(a) cout<<a<<"\n"
#define all(a)  (a).begin(),(a).end()
#define SORT(a) sort((a).begin(),(a).end())
#define oorret 0
#define oor(x) [&](){try{x;} catch(const out_of_range& oor){return oorret;} return x;}()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> P;
template<typename T1,typename T2> inline bool chmin(T1 &a,T2 b){if(a>b){a=b;return 1;}return 0;}
template<typename T1,typename T2> inline bool chmax(T1 &a,T2 b){if(a<b){a=b;return 1;}return 0;}

int n,m,R;

int main(){
    cin >> n >> m >> R;
    vector<int> r(R);
    REP(i,R){
        cin >> r[i];
        r[i]--;
    }
    vector<vector<int>> e(n,vector<int>(n,1e8));//infで初期化
    vector<int> a(m);
    vector<int> b(m);
    vector<int> c(m);
    REP(i,m){
        cin >> a[i] >> b[i] >> c[i];
        --a[i];
        --b[i];
        e[a[i]][b[i]] = c[i];
        e[b[i]][a[i]] = c[i];//無向グラフ
    }
    REP(i,n){
        e[i][i]=0;
    }
    
    vector<vector<int>> next(n,vector<int>(n,0));//頂点の遷移情報を記録
    REP(i,n){
        REP(j,n){
            next[i][j] = j;
        }
    }
    //ワーシャルフロイド法
    REP(k,n){
        REP(i,n){
            REP(j,n){
                if(chmin(e[i][j],e[i][k]+e[k][j])){
                    next[i][j]=next[i][k];
                }
            }
        }
    }
    int res = INT_MAX;
    vector<int> con;
    Rep(i,R){
        con.push_back(i);
    }
    do{
        int temp = 0;
        REP(i,R-1){
            temp+=e[r[con[i]]][r[con[i+1]]];
        }
        chmin(res,temp);
    }while(next_permutation(all(con)));
    put(res);
    return 0;
}
