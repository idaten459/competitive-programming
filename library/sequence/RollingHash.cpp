/*
RollingHash ある文字列sの部分文字列がtに一致するかという問題をO(|S|)で溶ける
boostを使わずに衝突の可能性を減らすため、複数の素数をmodにして全てが一致したらOKという形式にした。
hashの衝突確率は比較回数をnとすると1-(1-1/mod)^nであるからn=10^6でテストケース100個とかだと少し危うくなってくる(2個くらい入れてやればOK)
種類数を求める問題だとhashを使うと確率が跳ね上がるため、複数のmodが必須
詳しくは、 https://snuke.hatenablog.com/entry/2017/02/03/035524
今後の拡張としては[l,r)での検索が待たれる
計算量O(|S|)
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/ALDS1_14_B/judge/3795776/C++14
*/

class RollingHash {
private:
    const ull base;
    const vector<ull> mod;
    const int n;
public:
    RollingHash(const vector<ull>& mod,const ull& base) :mod(mod), base(base), n((int)mod.size()) {}
    bool contain(const string& s, const string& t) {//sのsubstringにtが存在するか
		return contain(s, t, 0, s.size());
	}
	bool contain(const string& s, const string& t, int l, int r) {//sの[l,r)にsubstringにtが存在するか
		int sl = (int)s.size(), tl = (int)t.size();
		int ran = r - l;
		if (ran < tl)return false;
		vector<ull> sh(n, 0), th(n, 0), p(n, 1);
		bool flag = true;
		for (int i = 0; i < n; ++i) {
			for (int j = l; j < l + tl; ++j) {
				sh[i] = sh[i] * base + s[j];
				if (sh[i] > mod[i])sh[i] %= mod[i];
				th[i] = th[i] * base + t[j-l];
				if (th[i] > mod[i])th[i] %= mod[i];
				p[i] *= base;
				if (p[i] > mod[i])p[i] %= mod[i];
			}
		}
		for (int i = 0; i < n; ++i) {
			if (th[i] != sh[i])flag = false;
		}
		if (flag) {
			return true;
		}
		for (int j = l + tl; j < r; ++j) {
			flag = true;
			for (int i = 0; i < n; ++i) {
				sh[i] = sh[i] * base + s[j];
				if (sh[i] < p[i] * s[j - tl]) {
					sh[i] += mod[i] * s[j - tl];
				}
				sh[i] -= p[i] * s[j - tl];
				if (sh[i] > mod[i])sh[i] %= mod[i];
			}
			for (int i = 0; i < n; ++i) {
				if (th[i] != sh[i])flag = false;
			}
			if (flag) {
				return true;
			}
		}
		return false;
	}
    vector<int> find(const string& s, const string& t){
        return find(s,t,0,s.size());
    }
    vector<int> find(const string& s, const string& t, int l, int r) {//sのsubstringがtである先頭のindexを返す
        int sl = (int)s.size(), tl = (int)t.size();
        vector<int> res;
        int ran = r - l;
		if (ran < tl)return res;
        vector<ull> sh(n,0),th(n,0),p(n,1);
        bool flag = true;
        for(int i=0;i<n;++i){
            for (int j = l; j < l + tl; ++j) {
                sh[i] = sh[i] * base + s[j];
                if (sh[i] > mod[i])sh[i] %= mod[i];
                th[i] = th[i] * base + t[j-l];
                if (th[i] > mod[i])th[i] %= mod[i];
                p[i] *= base;
                if (p[i] > mod[i])p[i] %= mod[i];
            }
        }
        for(int i=0;i<n;++i)if(th[i]!=sh[i])flag=false;
        if(flag)res.push_back(0);
        for (int j = l + tl; j < r; ++j) {
            flag = true;
            for(int i=0;i<n;++i){
                sh[i] = sh[i] * base + s[j];
                if (sh[i] < p[i] * s[j - tl]) {
                    sh[i] += mod[i] * s[j - tl];
                }
                sh[i] -= p[i] * s[j - tl];
                if (sh[i] > mod[i])sh[i] %= mod[i];
            }
            for(int i=0;i<n;++i)if (th[i] != sh[i])flag = false;
            if(flag)res.push_back(j-tl+1);
        }
        return res;
    }
};


int main() {
    string s , t;
    cin >> s >> t;
    random_device rnd;
    mt19937 mt(rnd());
    //Prime number about 10 ^ 9
    //999999797,999999883,999999893,999999929,999999937,1000000007,1000000009,1000000021,1000000033,1000000087
    const vector<ull> mod = {999999797,999999883,999999893,999999929,999999937,1000000007,1000000009,1000000021,1000000033,1000000087};
    const ull base = mt()+1e5;
    using RH = RollingHash;
    RH r(mod, base);
    vector<int> res = r.find(s, t);
    REP(i, res.size()) {
        put(res[i]);
    }
    return 0;
}
