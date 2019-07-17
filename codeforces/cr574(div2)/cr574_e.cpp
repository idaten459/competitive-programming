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

const ll inf = 1e10;


int main() {
	ll n, m, a, b;
	cin >> n >> m >> a >> b;
	ll g0, x, y, z;
	cin >> g0 >> x >> y >> z;
	vector<ll> g(n + m);
	g[0] = g0;
	REP(i, n * m-1) {
		g[i + 1] = (g[i] * x + y) % z;
	}
	vector<vector<ll>> h(n, vector<ll>(m, 0));
	REP(i, n) {
		REP(j, m) {
			h[i][j] = g[i * m + j];
		}
	}
	
	return 0;
}
