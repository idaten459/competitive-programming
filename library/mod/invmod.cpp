/*
1/2 = 500000004(mod 1e9+7)みたいなのを500000004から復元する
分母が十分小さいなら見つけられるはず
1e9+7に対し、loop=1e5回試しているので分母が1e4以下だと良さそう
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
	else fact<T>(n) / fact<T>(m) / fact<T>(n - m);
}

template<uint_fast64_t Mod>
class ModInt {
	using lint = int_fast64_t;
public:
	lint a;
	ModInt(lint val = 0) { if (val >= Mod) { val %= Mod; }a = val; }
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
	ModInt& operator++(int) { (*this) = (*this) + 1; return *this; }//前置インクリメントs(++a)のオーバーロード
	ModInt& operator++() { (*this) = (*this) + 1; return *this; }//後置インクリメント(a++)のオーバーロード
	ModInt& operator--(int) { (*this) = (*this) + (Mod - 1); return *this; }//前置デクリメント(--a)のオーバーロード
	ModInt& operator--() { (*this) = (*this) + (Mod - 1); return *this; }//後置デクリメント(a--)のオーバーロード
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

constexpr uint_fast64_t mod = 1e9 + 7;
//constexpr uint_fast64_t mod = 998244353;
using mi = ModInt<mod>;

template<typename T, typename U>
T gcd(T u, U v) {
	if (u == 0)return v;
	if (v == 0)return u;
	T r;
	while (v) {
		r = u % v;
		u = v;
		v = r;
	}
	return u;
}

template<typename T>
T gcd(vector<T> a) {
	int l = a.size();
	T res = 0;
	for (int i = 0; i < l; ++i) {
		res = gcd(res, a[i]);
	}
	return res;
}

void invmod(int n,int m=10) {
	for (int i = 0; i < m; ++i) {
		mi t = i + 1;
		mi res = t / n;
		cout << "n =" << t << "/" << res << "\n";
	}
	random_device seed_gen;
	mt19937 engine(seed_gen());
	const int l = 1e5;
	using P = pair<long long, long long>;
	set<P> st;
	for (int i = 0; i < l; ++i) {
		mi numer = engine()%mod; // 分子
		mi denom = numer / n; // 分母
		int g = gcd(numer.a, denom.a);
		numer /= g;
		denom /= g;
		
		st.insert(P(numer.a, denom.a));
	}
	int lim = 10;
	for (auto v : st) {
		cout << v.first << " " << v.second << "\n";
		if (--lim < 0) {
			break;
		}
	}
	return ;
}