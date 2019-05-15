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
    int n,C;
    cin >> n >> C;
    vector<int> s(n);
    vector<int> t(n);
    vector<int> c(n);
    REP(i,n){
        cin >> s[i] >> t[i] >> c[i];
        c[i]--;
    }
    vector<vector<bool>> channel(C,vector<bool>(1e5+10,false));
    REP(i,n){
        FOR(j,s[i]-1,t[i]){
            channel[c[i]][j]=true;
        }
    }
    int res = 0;
    REP(j,1e5+10){
        int temp = 0;
        REP(i,C){
            if(channel[i][j]){
                temp++;
            }
        }
        chmax(res,temp);
    }
    put(res);
    return 0;
}
