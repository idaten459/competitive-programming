/*
実行時に法が決まるmodint
定数倍高速化の恩恵が受けられず遅い
@verify https://atcoder.jp/contests/abc042/submissions/6727336
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
        T t = s;
        for (int_fast32_t i = s; i < n + 1; ++i) {
            table.push_back(table.back() * i);
        }
    }
    if (n < 0) return 1;
    else return table[n.a];
}

template<typename T>
inline T invfact(int_fast32_t n) {
    static vector<T> invtable(1, 1);
    if (n >= (int)invtable.size()) {
        uint_fast32_t s = invtable.size();
        for (T i = s; i < n + 1; ++i) {
            invtable.push_back(invtable.back() / i);
        }
    }
    if (n < 0) return 1;
    else return invtable[n];
}

template<typename T>
inline T comb(uint_fast32_t n, uint_fast32_t m, bool closed = true) {//nCm
    if (n < m)return 0;
    else if (closed)return fact<T>(n) * invfact<T>(m) * invfact<T>(n - m);
    else return fact<T>(n) / fact<T>(m) / fact<T>(n - m);
}

class RuntimeModInt {
    using lint = int_fast64_t;
    static lint &mod() {static lint Mod = 0;return Mod;}
public:
    lint a;
    RuntimeModInt(lint val = 0){if(val >= get_mod()){val %= get_mod();}else if(val < 0){val%=get_mod();val+=get_mod();}a=val;}
    static void set_mod(const lint x) { mod() = x; }
    static lint get_mod() { return mod(); }
    RuntimeModInt operator-() {return RuntimeModInt(get_mod() - a);}//単項-演算子(-a)のオーバーロード
    RuntimeModInt operator=(const RuntimeModInt& n) { a = n.a; return a; }
    RuntimeModInt operator+(const RuntimeModInt& n) { if ((a + n.a) >= get_mod()) { return a + n.a - get_mod(); } else { return a + n.a; } }
    RuntimeModInt operator-(const RuntimeModInt& n) {return a+(get_mod()-n.a);}
    RuntimeModInt operator*(const RuntimeModInt& n) { return a * n.a; }
    RuntimeModInt operator/(const RuntimeModInt& n) { return (*this) * pow(n, get_mod() - 2); }
    RuntimeModInt& operator+=(const RuntimeModInt& n) { (*this) = (*this) + n; return *this; }
    RuntimeModInt& operator-=(const RuntimeModInt& n) { (*this) = (*this) + (get_mod()-n.a); return *this; }
    RuntimeModInt& operator*=(const RuntimeModInt& n) { (*this) = (*this) * n; return *this; }
    RuntimeModInt& operator/=(const RuntimeModInt& n) { (*this) = (*this) / n; return *this; }
    RuntimeModInt& operator++(int) { RuntimeModInt a=*this;(*this) += 1; return a; }//後置
    RuntimeModInt& operator++() { (*this) += 1; return *this; }//前置
    RuntimeModInt& operator--(int) { RuntimeModInt a=*this;(*this) -= 1; return a; }//後置
    RuntimeModInt& operator--() { (*this) -= 1; return *this; }//前置
    RuntimeModInt inv() { RuntimeModInt temp(1); return temp / (*this); }//逆数を返す関数
    bool operator<(const RuntimeModInt& n) { return a < n.a; }
    bool operator<=(const RuntimeModInt& n) { return a <= n.a; }
    bool operator>(const RuntimeModInt& n) { return a > n.a; }
    bool operator>=(const RuntimeModInt& n) { return a >= n.a; }
    bool operator==(const RuntimeModInt& n) { return a == n.a; }
    bool operator!=(const RuntimeModInt& n) { return a != n.a; }
    //下の関係演算子はpow関数で要請される
    bool operator<(const int& n) { return a < n; }
    bool operator<=(const int& n) { return a <= n; }
    bool operator>(const int& n) { return a > n; }
    bool operator>=(const int& n) { return a >= n; }
    bool operator==(const int& n) { return a == n; }
    RuntimeModInt operator%(const int& n) { return a % n; }
};
inline ostream& operator <<(ostream& o, const RuntimeModInt& t) {o << t.a;return o;}
inline istream& operator >>(istream& i, RuntimeModInt& t) {i >> t.a;return i;}

int main(){
    uint_fast64_t mod = 1e9+7;
    RuntimeModInt::set_mod(mod);
    using mi = RuntimeModInt;
}