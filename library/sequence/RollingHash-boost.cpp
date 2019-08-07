/*
    rollinghashの実装
    10^9+7だと落ちるhashが衝突するという怪情報をみたので、一応boostを使ってMOD=10^18+9で実装して、
    BASEを乱数にしたことで特定のhackcaseが生じることもなくなった。
    sのsubstringがtである先頭のindexの検索をO(N+M)で行える。
    今後の拡張としては[l,r)での検索とかかな
    なおboostはAOJとAtCoderしか使えなさそうであった。
    codeforces,yukicoderはだめだった、その場合ullにしてMOD=1e9+9くらいにしておくとよさそう
    @verify 
    https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/ALDS1_14_B/judge/3785365/C++14
    https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/ALDS1_14_B/judge/3785357/C++14
    https://yukicoder.me/submissions/364720
*/

template<typename T>
class RollingHash {
private:
	const T mod, base;
	//T sh = 0, th = 0, p = 1;
public:
	RollingHash(const T& mod,const T& base) :mod(mod), base(base) {}
	bool contain(const string& s, const string& t) {//sのsubstringにtが存在するか
		int sl = s.size(), tl = t.size();
		T sh = 0, th = 0, p = 1;
		if (sl < tl)return false;
		for (int i = 0; i < tl; ++i) {
			sh = sh * base + s[i];
			if (sh > mod)sh %= mod;
			th = th * base + t[i];
			if (th > mod)th %= mod;
			p *= base;
			if (p > mod)p %= mod;
		}
		if (th == sh)return true;
 		for (int i = tl; i < sl; ++i) {
			sh = sh * base + s[i];
			if (sh < p * s[i - tl]) {
				sh += mod * s[i - tl];
			}
			sh -= p * s[i - tl];
			if (th > mod)sh %= mod;
			if (th == sh)return true;
		}
		return false;
	}
	vector<int> find(const string& s, const string& t) {//sのsubstringがtである先頭のindexを返す
		int sl = s.size(), tl = t.size();
		T sh = 0, th = 0, p = 1;
		vector<int> res;
		if (sl < tl)return res;
		for (int i = 0; i < tl; ++i) {
			sh = sh * base + s[i];
			if (sh > mod)sh %= mod;
			th = th * base + t[i];
			if (th > mod)th %= mod;
			p *= base;
			if (p > mod)p %= mod;
		}
		if (th == sh)res.push_back(0);
		for (int i = tl; i < sl; ++i) {
			sh = sh * base + s[i];
			if (sh < p * s[i - tl]) {
				sh += mod * s[i - tl];
			}
			sh -= p * s[i - tl];
			if (sh > mod)sh %= mod;
			if (th == sh)res.push_back(i-tl+1);
		}
		return res;
	}
};

#include <boost/multiprecision/cpp_int.hpp>

int main() {
	namespace mp = boost::multiprecision;
	using u128 = mp::uint128_t;
	string s , t;
	cin >> s >> t;
	random_device rnd;
	mt19937 mt(rnd());
	const u128 mod = (u128)1e18 + 9;
	const u128 base = (u128)mt() % mod + (u128)1e9;
	using RH = RollingHash<u128>;
	RH r(mod, base);
	vector<int> res = r.find(s, t);
	REP(i, res.size()) {
		put(res[i]);
	}
	
	return 0;
}
