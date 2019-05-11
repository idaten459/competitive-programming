#include "bits/stdc++.h"
#include <unistd.h>
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

vector<double> table;

double logfact(int n){
    if(table[n]>=0){
        return table[n];
    }
    double res = (double)log10(n)+logfact(n-1);
    table[n] = res;
    return res;
}

double logpow(int n,int m){
    return (double)m*log10(n);
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<int> r(m);
    REP(i,m){
        cin >> r[i];
    }
    table.resize(n+1);
    fill(all(table),-1);
    table[0]=0;
    double p=0;
    p+=logfact(n);
    REP(i,m){
        p-=logfact(r[i]);
    }
    p-=logpow(m,n);
    put(-floor(p));
    return 0;
}
