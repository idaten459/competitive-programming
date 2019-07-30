/*
ModIntに対応したpow,fact,combを作ることで、軽量化に成功し、気軽に初期化できるようになった
使用例も一緒に載せてあるので、使い方はmain関数ないを参考されたし
標準入出力に対応
abc042dの「いろはちゃんとます目」で動作確認済み
@verify https://atcoder.jp/contests/abc132/submissions/6611055
！注意！
comb使うときは、n<mの時、comb(n,m)=0とした。combは、
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
        ll s = table.size();
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

class ModInt {
public:
    ll a;
    const int mod = 1e9 + 7;
    ModInt(ll _val = 0) {
        if (_val >= mod) { _val %= mod; }
        a = _val;
    }
    ModInt operator-() {return ModInt(mod - a);}//単項-演算子(-a)のオーバーロード
    ModInt operator=(const ModInt n) { a = n.a; return a; }
    ModInt operator+(const ModInt n) { if ((a + n.a) >= mod) { return a + n.a - mod; } else { return a + n.a; } }
    ModInt operator-(const ModInt n) {return a+(mod-n.a);}
    ModInt operator*(const ModInt n) { return a * n.a; }
    ModInt operator/(const ModInt n) { return (*this) * pow(n, mod - 2); }
    ModInt& operator+=(const ModInt n) { (*this) = (*this) + n; return *this; }
    ModInt& operator-=(const ModInt n) { (*this) = (*this) + (mod-n.a); return *this; }
    ModInt& operator*=(const ModInt n) { (*this) = (*this) * n; return *this; }
    ModInt& operator/=(const ModInt n) { (*this) = (*this) / n; return *this; }
    ModInt& operator++(int) { (*this) = (*this) + 1; return *this; }//前置インクリメントs(++a)のオーバーロード
    ModInt& operator++() { (*this) = (*this) + 1; return *this; }//後置インクリメント(a++)のオーバーロード
    ModInt& operator--(int) { (*this) = (*this) + (mod-1); return *this; }//前置デクリメント(--a)のオーバーロード
    ModInt& operator--() { (*this) = (*this) + (mod-1); return *this; }//後置デクリメント(a--)のオーバーロード
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
ostream& operator <<(ostream& o, const ModInt& t) {
    o << t.a;
    return o;
}
istream& operator >>(istream& i, ModInt& t) {
    i >> t.a;
    return i;
}
