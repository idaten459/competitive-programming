#include "bits/stdc++.h"
using namespace std;
#define Rep(i,n) for(int i=0;i<(int)(n);i++)
#define For(i,n1,n2) for(int i=(int)(n1);i<(int)(n2);i++)
#define REP(i,n) for(ll i=0;i<(ll)(n);i++)
#define RREP(i,n) for(ll i=((ll)(n)-1);i>=0;i--)
#define FOR(i,n1,n2) for(ll i=(ll)(n1);i<(ll)(n2);i++)
#define RFOR(i,n1,n2) for(ll i=((ll)(n1)-1);i>=(ll)(n2);i--)
#define put(a) cout<<a<<"\n"
#define all(a)  (a).begin(),(a).end()
#define SORT(a) sort((a).begin(),(a).end())
#define oorret 0
#define oor(x) [&](){try{x;} catch(const out_of_range& oor){return oorret;} return x;}()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
template<typename T1, typename T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return 1; }return 0; }
template<typename T1, typename T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return 1; }return 0; }

int main() {
	int n;
	cin >> n;
	vector<ll> h1(n);
	vector<ll> h2(n);
	vector<vector<ll>> h(n, vector<ll>(2, 0));
	REP(i, n) {
		cin >> h[i][0];
	}
	REP(i, n) {
		cin >> h[i][1];
	}
	vector<vector<ll>> dp(n, vector<ll>(2, 0));
	dp[0][0] = h[0][0];
	dp[0][1] = h[0][1];
	REP(i, n-1) {
		REP(j, 2) {
			dp[i + 1][j] = max(dp[i][j], dp[i][1 - j] + h[i + 1][j]);
		}
		
	}
	put(max(dp[n - 1][0], dp[n - 1][1]));
	return 0;
}