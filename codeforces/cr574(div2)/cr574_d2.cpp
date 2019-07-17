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
	if (n - m < m)return comb(n, n - m, table);
	else return fact(n, table) / fact(m, table) / fact(n - m, table);
}

class ModInt {
public:
	ll a;
	const int mod = 998244353;
	ModInt(ll _val = 0) {
		if (_val >= mod) { _val %= mod; }
		a = _val;
	}
	ModInt operator-() { return ModInt(mod - a); }//単項-演算子(-a)のオーバーロード
	ModInt operator=(const ModInt n) { a = n.a; return a; }
	ModInt operator+(const ModInt n) { if ((a + n.a) >= mod) { return a + n.a - mod; } else { return a + n.a; } }
	ModInt operator-(const ModInt n) { return a + (mod - n.a); }
	ModInt operator*(const ModInt n) { return a * n.a; }
	ModInt operator/(const ModInt n) { return (*this) * pow(n, mod - 2); }
	ModInt& operator+=(const ModInt n) { (*this) = (*this) + n; return *this; }
	ModInt& operator-=(const ModInt n) { (*this) = (*this) + (mod - n.a); return *this; }
	ModInt& operator*=(const ModInt n) { (*this) = (*this) * n; return *this; }
	ModInt& operator/=(const ModInt n) { (*this) = (*this) / n; return *this; }
	ModInt& operator++(int) { (*this) = (*this) + 1; return *this; }//前置インクリメントs(++a)のオーバーロード
	ModInt& operator++() { (*this) = (*this) + 1; return *this; }//後置インクリメント(a++)のオーバーロード
	ModInt& operator--(int) { (*this) = (*this) + (mod - 1); return *this; }//前置デクリメント(--a)のオーバーロード
	ModInt& operator--() { (*this) = (*this) + (mod - 1); return *this; }//後置デクリメント(a--)のオーバーロード
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


int main() {
	int n;
	cin >> n;
	vector<string> a(n);
	REP(i, n) {
		cin >> a[i];
	}
	vector<ModInt> b(n, 0);
	vector<vector<ModInt>> c1(n,vector<ModInt>(10,0));
	vector<vector<ModInt>> c2(n,vector<ModInt>(10,0));
	vector<vector<ModInt>> d(n,vector<ModInt>(10,0));
	vector<ModInt> keta(10, 0);
	REP(i, n) {
		keta[a[i].size() - 1]++;
	}
	REP(i, n) {
		//string temp = "";
		REP(k, 10) {
			//if (k + 1 < a[i].size()) {
				REP(j, a[i].size()) {
					if (j >= a[i].size()-k-1) {
						c1[i][k] *= 10;
					}
					//c1[i][k] += a[i][j] - '0';
					c1[i][k] *= 10;
					c1[i][k] += a[i][j] - '0';
					
					c2[i][k] *= 10;
					c2[i][k] += a[i][j] - '0';
					if (j >= a[i].size() - k - 1) {
						c2[i][k] *= 10;
					}
					//c2[i][k] += a[i][j] - '0';
				}
			/*}
			else {
				REP(j, a[i].size()) {
					c1[i][k] *= 10;
					c1[i][k] += a[i][j] - '0';
					c1[i][k] *= 10;
					c1[i][k] += a[i][j] - '0';
					
					c2[i][k] *= 10;
					c2[i][k] += a[i][j] - '0';
					c2[i][k] *= 10;
					c2[i][k] += a[i][j] - '0';
				}
			}*/
		}
		

	}
	REP(i, n) {
		REP(j, 10) {
			d[i][j] = c1[i][j] + c2[i][j];
		}
	}
	ModInt res;
	REP(i, n) {
		REP(j, 10) {
			/*if (j == a[i].size() - 1) {
				res += (keta[j] - 1) * d[i][j];
			}
			else {
				res += keta[j] * d[i][j];
			}*/
			res += c1[i][j] * keta[j];
			res += c2[i][j] * keta[j];
		}
	}
	put(res);
 	return 0;
}
