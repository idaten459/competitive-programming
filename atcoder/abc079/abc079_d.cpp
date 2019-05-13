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

int main(){
    int h,w;
    cin >> h >> w;
    vector<vector<int>> c(10,vector<int>(10));
    REP(i,10){
        REP(j,10){
            cin >> c[i][j];
        }
    }
    vector<vector<int>> a(h,vector<int>(w));
    vector<int> cnt(10,0);
    REP(i,h){
        REP(j,w){
            cin >> a[i][j];
            if(a[i][j]>=0){
                cnt[a[i][j]]++;
            }
        }
    }
    vector<int> d(10,INT_MAX/2);
    d[1] = 0;
    priority_queue<int,vector<int>,greater<int>> q;
    q.push(1);
    while(!q.empty()){
        int p = q.top();
        q.pop();
        Rep(i,10){
            int to = i;
            if(i!=p){
                if(d[to]>d[p]+c[to][p]){
                    d[to]=d[p]+c[to][p];
                    q.push(to);
                }
            }
        }
    }
    int res = 0;
    REP(i,10){
        res+=d[i]*cnt[i];
    }
    put(res);
    return 0;
}
