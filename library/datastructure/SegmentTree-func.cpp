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
typedef pair<int, int> P;
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

template<typename T>
T upsum(const T& l, const T& r) {//SegmentTreeのupdate関数
    T res;
    res = l + r;
    return res;
}

template<typename T>
class SegmentTree {
public:
    using F = function<T(T&, T&)>;
    vector<T> seg;
    int sz = 1;
    T unit;
    F up;
    SegmentTree(int n, F up, T unit = 0):up(up),unit(unit) {
        while (sz < n) sz <<= 1;
        seg.resize(sz * 2, unit);
    }
    void set(const int& k, const T& x) {//左からk番目の葉にxを代入する
        seg[sz - 1 + k] = x;
    }
    T get(const int& k) {//左からk番目の葉を得る
        return seg[sz - 1 + k];
    }
    void update(int k, T v) {// k 番目の値をup(seg[k],v)にする
		k += sz - 1;
		seg[k] = up(seg[k], v);
		while (k > 0) {
			k = (k - 1) / 2;
			seg[k] = up(seg[2 * k + 1], seg[2 * k + 2]);
		}
	}
    T query(int a, int b) {//[a,b)のupの合成を求める
        int k = 0, l = 0, r = sz;
        if (r <= a || b <= l) {
            return unit;
        }
        if (a <= l && r <= b) {
            return seg[k];
        }
        else {
            T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return up(vl, vr);
        }
    }
    T query(int a, int b, int k, int l, int r) {//[a,b)のupの合成を求める(a,b,0,0,sz)のように使う
        if (r <= a || b <= l) {
            return unit;
        }
        if (a <= l && r <= b) {
            return seg[k];
        }
        else {
            T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return up(vl, vr);
        }
    }
};



int main(){
    SegmentTree<int> sgmax(n,upmax<int>,-1);
    vector<SegmentTree<ll>> sg(n, SegmentTree<ll>(n, upsum<ll>, 0));
}

/*
@verify https://atcoder.jp/contests/agc005/submissions/5715080
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_B/judge/3781776/C++14
*/
