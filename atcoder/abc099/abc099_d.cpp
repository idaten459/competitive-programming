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
    int n,c;
    cin >> n >> c;
    vector<vector<int>> d(c,vector<int>(c));
    vector<vector<int>> b(n,vector<int>(n));
    REP(i,c){
        REP(j,c){
            cin >> d[i][j];
        }
    }
    REP(i,n){
        REP(j,n){
            cin >> b[i][j];
            b[i][j]--;
        }
    }
    vector<vector<int>> s(3,vector<int>(c,0));
    REP(i,n){
        REP(j,n){
            s[(i+j)%3][b[i][j]]++;
        }
    }
    vector<int> com (c,0);
    REP(i,3)com[i]=1;
    reverse(all(com));
    int res = INT_MAX;
    REP(i,c){
        REP(j,c){
            REP(k,c){
                if(i!=j&&j!=k&&k!=i){
                    int temp = 0;
                    REP(m,c){
                        temp+=d[m][i]*s[0][m];
                        temp+=d[m][j]*s[1][m];
                        temp+=d[m][k]*s[2][m];
                        
                    }
                    chmin(res,temp);
                }
            }
        }
    }
    put(res);
    return 0;
}
