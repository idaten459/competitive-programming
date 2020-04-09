#include "bits/stdc++.h"
#define Rep(i,n) for(int i=0;i<(int)(n);i++)
#define For(i,n1,n2) for(int i=(int)(n1);i<(int)(n2);i++)
#define REP(i,n) for(ll i=0;i<(ll)(n);i++)
#define RREP(i,n) for(ll i=((ll)(n)-1);i>=0;i--)
#define FOR(i,n1,n2) for(ll i=(ll)(n1);i<(ll)(n2);i++)
#define RFOR(i,n1,n2) for(ll i=((ll)(n1)-1);i>=(ll)(n2);i--)
#define all(a)  (a).begin(),(a).end()
#define IOS std::cin.tie(0),std::ios::sync_with_stdio(false)

namespace idaten{

using namespace std;
using ll = int_fast64_t;
using ull = uint_fast64_t;
using P = std::pair<int64_t, int64_t>;
template<typename T1, typename T2> inline bool chmin(T1& a, T2 b) { if (a > b) { a = b; return 1; }return 0; }
template<typename T1, typename T2> inline bool chmax(T1& a, T2 b) { if (a < b) { a = b; return 1; }return 0; }
template<class Type>struct is_vector : std::false_type {};
template<class ValueType, class Alloc>struct is_vector<std::vector<ValueType, Alloc>> : std::true_type {};
template <typename T> inline std::ostream& operator << (std::ostream& out, const std::vector<T>& v) {
    if (v.empty())return out;
    constexpr bool is_vector_v = is_vector<T>::value;
    if (is_vector_v)for (auto itr = v.begin(); itr != v.end();)out << (*itr), out << ((++itr != v.end()) ? "\n" : "");
    else for (auto itr = v.begin(); itr != v.end();)out << (*itr), out << ((++itr != v.end()) ? " " : "");
    return out;
}
inline void put() {}
template<class T> inline void put(const T& first) { std::cout << first << "\n"; }
template<class T, class... N> inline void put(const T& first, const N& ... rest) { std::cout << first << " "; put(rest...); }
inline void putn() {}
template<class T, class... N> inline void putn(const T& first, const N& ... rest) { std::cout << first << "\n"; putn(rest...); }


void solve(){
    IOS;
}
} // namespace idaten

int main(){
    idaten::solve();
    return 0;
}
