#include "bits/stdc++.h"
#define Rep(i,n) for(int i=0;i<(int)(n);i++)
#define For(i,n1,n2) for(int i=(int)(n1);i<(int)(n2);i++)
#define REP(i,n) for(ll i=0;i<(ll)(n);i++)
#define RREP(i,n) for(ll i=((ll)(n)-1);i>=0;i--)
#define FOR(i,n1,n2) for(ll i=(ll)(n1);i<(ll)(n2);i++)
#define RFOR(i,n1,n2) for(ll i=((ll)(n1)-1);i>=(ll)(n2);i--)
#define all(a)  (a).begin(),(a).end()
#define IOS std::cin.tie(0),std::ios::sync_with_stdio(false)

namespace idaten {

using namespace std;
using ll = int_fast64_t;
using ull = uint_fast64_t;
using P = std::pair<int64_t, int64_t>;
template<typename T1, typename T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return 1; }return 0; }
template<typename T1, typename T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return 1; }return 0; }
template<class T> inline std::istream& operator >> (std::istream& is, std::vector<T>& v) { for (T& x : v) { is >> x; }return is; }
template<class T> inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
	for (auto itr = v.begin(); itr != v.end();) { os << (*itr) << ((++itr != v.end()) ? " " : ""); }
	return os;
}
template<class V, typename T>inline void fill(V& v, const T& val) { v = val; }
template<class V, typename T>inline void fill(std::vector<V>& v, const T& val) { for (V& x : v) { fill(x, val); } }
template<class V, typename H>inline void resize(std::vector<V>& v, const H h) { v.resize(h); }
template<class V, typename H, typename... T>inline void resize(std::vector<V>& v, const H& h, const T& ... t) { v.resize(h); for (auto& x : v) { resize(x, t...); } }
inline void put() {}
template<class T> inline void put(const T& first) { std::cout << first << "\n"; }
template<class T, class... N> inline void put(const T& first, const N& ... rest) { std::cout << first << " "; put(rest...); }

void solve() {
	IOS;
}
} // namespace idaten

int main() {
	idaten::solve();
	return 0;
}
