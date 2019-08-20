/*
実行前に法が与えられているModInt
定数による高速化の恩恵を得られる
@verify https://atcoder.jp/contests/abc042/submissions/6726858
        https://atcoder.jp/contests/abc042/submissions/6942247 (add invfact, comb(...,invtable),)
！注意！
comb使うときは、n<mの時、comb(n,m)=0とした。combは、n,mがもともとintであることが前提となっている
*/

template<typename T, typename U>
inline T pow(T x, U exp) {
    if (exp <= 0) {
        return 1;
    }
    if (exp % 2 == 0) {
        T d = pow(x, exp / 2);
        return d * d;
    }
    else {
        return (x * pow(x, exp - 1));
    }
}

template<typename T>
inline T fact(T n, vector<T>& table) {
    if (n >= (int)table.size()) {
        uint_fast32_t s = table.size();
        for (T i = s; i < n + 1; ++i) {
            table.push_back(table.back() * i);
        }
    }
    if (n < 0) return 1;
    else return table[n.a];
}

template<typename T>
inline T comb(T n, T m, vector<T>& table) {//nCm
    if (n < m)return 0;
    if (n - m < m)return comb(n, n - m, table);
    else return fact(n, table) / fact(m, table) / fact(n - m, table);
}

template<uint_fast64_t Mod>
class ModInt {
    using lint = int_fast64_t;
public:
    lint a;
    ModInt(lint val = 0){if(val >= Mod){val %= Mod;}a=val;}
    ModInt operator-() {return ModInt(Mod - a);}//単項-演算子(-a)のオーバーロード
    ModInt operator=(const ModInt n) { a = n.a; return a; }
    ModInt operator+(const ModInt n) { if ((a + n.a) >= Mod) { return a + n.a - Mod; } else { return a + n.a; } }
    ModInt operator-(const ModInt n) {return a+(Mod-n.a);}
    ModInt operator*(const ModInt n) { return a * n.a; }
    ModInt operator/(const ModInt n) { return (*this) * pow(n, Mod - 2); }
    ModInt& operator+=(const ModInt n) { (*this) = (*this) + n; return *this; }
    ModInt& operator-=(const ModInt n) { (*this) = (*this) + (Mod-n.a); return *this; }
    ModInt& operator*=(const ModInt n) { (*this) = (*this) * n; return *this; }
    ModInt& operator/=(const ModInt n) { (*this) = (*this) / n; return *this; }
    ModInt& operator++(int) { (*this) = (*this) + 1; return *this; }//前置インクリメントs(++a)のオーバーロード
    ModInt& operator++() { (*this) = (*this) + 1; return *this; }//後置インクリメント(a++)のオーバーロード
    ModInt& operator--(int) { (*this) = (*this) + (Mod-1); return *this; }//前置デクリメント(--a)のオーバーロード
    ModInt& operator--() { (*this) = (*this) + (Mod-1); return *this; }//後置デクリメント(a--)のオーバーロード
    ModInt inv() { ModInt temp(1); return temp / (*this); }//逆数を返す関数 return (*this)/(*this)/(*this);でもいい
    bool operator<(const ModInt n) { return a < n.a; }
    bool operator<=(const ModInt n) { return a <= n.a; }
    bool operator>(const ModInt n) { return a > n.a; }
    bool operator>=(const ModInt n) { return a >= n.a; }
    bool operator==(const ModInt n) { return a == n.a; }
    bool operator!=(const ModInt n) { return a != n.a; }
    //下の関係演算子はpow関数で要請される
    bool operator<(const int n) { return a < n; }
    bool operator<=(const int n) { return a <= n; }
    bool operator>(const int n) { return a > n; }
    bool operator>=(const int n) { return a >= n; }
    bool operator==(const int n) { return a == n; }
    ModInt operator%(const int n) { return a % n; }
};
template<uint_fast64_t Mod> inline
ostream& operator <<(ostream& o, const ModInt<Mod>& t) {
    o << t.a;
    return o;
}
template<uint_fast64_t Mod> inline
istream& operator >>(istream& i, ModInt<Mod>& t) {
    i >> t.a;
    return i;
}

constexpr uint_fast64_t mod = 1e9+7;
using mi = ModInt<mod>;

//static使うことでtableを省略できるかも！