#include "bits/stdc++.h"
using namespace std;
#define Rep(i,n) for(int i=0;i<(int)(n);i++)
#define For(i,n1,n2) for(int i=(int)(n1);i<(int)(n2);i++)
#define REP(i,n) for(ll i=0;i<(ll)(n);i++)
#define RREP(i,n) for(ll i=((ll)(n)-1);i>=0;i--)
#define FOR(i,n1,n2) for(ll i=(ll)(n1);i<(ll)(n2);i++)
#define RFOR(i,n1,n2) for(ll i=((ll)(n1)-1);i>=(ll)(n2);i--)
#define all(a)  (a).begin(),(a).end()
#define SORT(a) sort((a).begin(),(a).end())
#define oorret 0
#define oor(x) [&](){try{x;} catch(const out_of_range& oor){return oorret;} return x;}()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
template<typename T1, typename T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return 1; }return 0; }
template<typename T1, typename T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return 1; }return 0; }
template<class Type>struct is_vector : std::false_type {};
template<class ValueType, class Alloc>struct is_vector<std::vector<ValueType, Alloc>> : std::true_type {};
template <typename T> inline ostream& operator << (ostream& out, const vector<T>& v) {
	if (v.empty())return out;
	constexpr bool is_vector_v = is_vector<T>::value;
	if (is_vector_v)for (auto itr = v.begin(); itr != v.end();)out << (*itr),out << ((++itr != v.end()) ? "\n" : "");
	else for (auto itr = v.begin(); itr != v.end();)out << (*itr),out << ((++itr != v.end()) ? " " : "");
	return out;
}
inline void put() {}
template<class T> inline void put(const T& first) { std::cout << first; printf("\n"); }
template<class T, class... N> inline void put(const T& first, const N& ... rest) { std::cout << first; printf(" "); put(rest...); }
inline void putn() {}
template<class T, class... N> inline void putn(const T& first, const N& ... rest) { std::cout << first; printf("\n"); putn(rest...); }
