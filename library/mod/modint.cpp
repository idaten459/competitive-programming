/*
実行前に法が与えられているModInt
定数による高速化の恩恵を得られる
@verify https://atcoder.jp/contests/abc042/submissions/6726858
        https://atcoder.jp/contests/abc042/submissions/6942247 (add invfact, comb(...,invtable),)
		https://atcoder.jp/contests/abc042/submissions/7044773 (add static)
！注意！
comb使うときは、n<mの時、comb(n,m)=0とした。combは、n,mがもともとintであることが前提となっている
Modは正が想定されるので、unsigned にしていたが、signed との比較でかなりやばが発生していたので、signedに変更
*/

template<typename T, typename U>
inline T pow(T x, U exp) {
	if (exp <= 0) {
		return 1;
	}
	if (exp % 2 == 0) {
		T d = pow(x, exp / 2);
		return d * d;
	} else {
		return (x * pow(x, exp - 1));
	}
}

template<typename T>
inline T fact(int_fast32_t n) {
	static vector<T> table(1, 1);
	if (n >= (int)table.size()) {
		uint_fast32_t s = table.size();
		for (T i = s; i < n + 1; ++i) {
			table.push_back(table.back() * i);
		}
	}
	if (n < 0) return 1;
	else return table[n];
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

template<int_fast64_t Mod>
class ModInt {
	using lint = int_fast64_t;
public:
	lint a;
	ModInt(lint val = 0) { if (val >= Mod) { val %= Mod; } else if (val < 0) { val %= Mod; val += Mod; }a = val; }
	ModInt operator-() { return ModInt(Mod - a); }//単項-演算子(-a)のオーバーロード
	ModInt operator=(const ModInt n) { a = n.a; return a; }
	ModInt operator+(const ModInt n) { if ((a + n.a) >= Mod) { return a + n.a - Mod; } else { return a + n.a; } }
	ModInt operator-(const ModInt n) { return a + (Mod - n.a); }
	ModInt operator*(const ModInt n) { return a * n.a; }
	ModInt operator/(const ModInt n) { return (*this) * pow(n, Mod - 2); }
	ModInt& operator+=(const ModInt n) { (*this) = (*this) + n; return *this; }
	ModInt& operator-=(const ModInt n) { (*this) = (*this) + (Mod - n.a); return *this; }
	ModInt& operator*=(const ModInt n) { (*this) = (*this) * n; return *this; }
	ModInt& operator/=(const ModInt n) { (*this) = (*this) / n; return *this; }
	ModInt& operator++(int) { (*this) += 1; return *this; }//前置インクリメントs(++a)のオーバーロード
	ModInt& operator++() { (*this) += 1; return *this; }//後置インクリメント(a++)のオーバーロード
	ModInt& operator--(int) { (*this) -= 1; return *this; }//前置デクリメント(--a)のオーバーロード
	ModInt& operator--() { (*this) -= 1; return *this; }//後置デクリメント(a--)のオーバーロード
	ModInt inv() { return (ModInt)1 / (*this); }//逆数を返す関数
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
template<int_fast64_t Mod> inline ostream& operator <<(ostream& o, const ModInt<Mod>& t) { o << t.a; return o; }
template<int_fast64_t Mod> inline istream& operator >>(istream& i, ModInt<Mod>& t) { i >> t.a; return i; }

constexpr int_fast64_t mod = 1e9 + 7;
//constexpr int_fast64_t mod = 998244353;
using mi = ModInt<mod>;