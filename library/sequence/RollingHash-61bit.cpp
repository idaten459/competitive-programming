/*
RollingHash ある文字列sの長さlenの部分文字列のhashをO(|S|)で計算する
種類数を求める問題だとhashを使うと確率が跳ね上がるため、複数のmodが必須
詳しくは、 https://snuke.hatenablog.com/entry/2017/02/03/035524
mod = 2^61-1を使ったこのmodはかなり強いため、衝突の危険性はほとんどない上、速い
さらにbaseを複数使えるようにした
len,rが文字列の長さを超えていると実行時エラーになるので注意
計算量O(|S|)
@verify https://atcoder.jp/contests/abc141/submissions/10488333
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/ALDS1_14_B/judge/4225437/C++14
*/

template <uint_fast64_t basesize>
class RollingHash {
public:
	using u64 = uint_fast64_t;
	using i32 = int_fast32_t;
	using arr = array<u64, basesize>;
	const u64 mod = (1ull << 61) - 1;
	const u64 m30 = (1ull << 30) - 1;
	const u64 m31 = (1ull << 31) - 1;
	const u64 p31 = (1ull << 31);
	arr base;
	RollingHash() {
		random_device seed_gen;
		mt19937_64 engine(seed_gen());
		for (u64 i = 0; i < basesize; ++i) {
			base[i] = (engine() & m30) + m30;
		}
	}
	u64 mul(u64 a, u64 b) {
		u64 au = a >> 31;
		u64 ad = a & m31;
		u64 bu = b >> 31;
		u64 bd = b & m31;
		u64 mid = ad * bu + au * bd;
		u64 midu = mid >> 30;
		u64 midd = mid & m30;
		u64 res = au * bu * 2 + midu + (midd << 31) + ad * bd;
		return res;
	}
	u64 calcMod(u64 v) {
		v = (v & mod) + (v >> 61);
		if (v > mod)v - mod;
		return v;
	}
	vector<arr> calcHash(string &s,i32 l,i32 r) { // s[l,r)のhashを計算
		if (l >= r || r > s.size() || l < 0) return vector<arr>(0);
		vector<arr> res(r - l);
		for (i32 j = 0; j < basesize ; ++j) {
			res[0][j] = s[l];
		}
		for (i32 i = 1; i < r - l; ++i) {
			for (i32 j = 0; j < basesize; ++j) {
				res[i][j] = calcMod(mul(res[i - 1][j], base[j]) + s[i + l]);
			}
		}
		return res;
	}
	vector<arr> calcHashLen(string& s, i32 len) {
		if (len > s.size()) return vector<arr>(0);
		i32 l = (i32)s.size() - len + 1;
		vector<arr> pre = calcHash(s, 0, len);
		vector<arr> res(l);
		const u64 pos = mod * 3;
		arr p;
		fill(p.begin(), p.end(), 1);
		if (0 < len) {
			for (i32 j = 0; j < basesize; ++j) {
				res[0][j] = pre[len - 1][j];
			}
		}
		for (i32 i = 0; i < len; ++i) {
			for (i32 j = 0; j < basesize; ++j) {
				p[j] = calcMod(mul(p[j], base[j]));
			}
		}
		for (i32 i = 1; i < l; ++i) {
			for (i32 j = 0; j < basesize; ++j) {
				res[i][j] = calcMod(mul(res[i - 1][j], base[j]) + s[i - 1 + len]);//添え字周りが怪しい
				res[i][j] = calcMod(res[i][j] + pos - mul(s[i - 1], p[j]));				
			}
		}
		return res;
	}
};

constexpr uint_fast64_t  bs = 2;
using arr = array<uint_fast64_t, bs>;
using rh = RollingHash<bs>;