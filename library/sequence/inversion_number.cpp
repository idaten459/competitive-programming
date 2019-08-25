/*
転倒数を求める
転倒数の定義は、数列{an}に対して、i<j,ai>ajを満たす(i,j)の数
求め方は https://qiita.com/wisteria0410ss/items/296e0daa9e967ca71ed6 を参考にした
i=[0,n)に対して、a[i]の小さい順にseg[i]に1を加えてsegの[i+1,n)の和の合計が転倒数
(st.query(c[i].second+1, n)はc[i].second=kに対して、k<jかつa_K>a_jとなるjの個数)
@verify https://atcoder.jp/contests/chokudai_s001/submissions/7132271
		https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/ALDS1_5_D/judge/3828535/C++14
{an}に同じ数が含まれていても正しく動作する
計算量はO(NlogN)
*/

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
	SegmentTree(int n, F up, T unit = 0) :up(up), unit(unit) {
		while (sz < n) sz <<= 1;
		seg.resize(sz * 2, unit);
	}
	void set(const int& k, const T& x) {//左からk番目の葉にxを代入する
		seg[sz - 1 + k] = x;
	}
	T get(const int& k) {//左からk番目の葉を得る
		return seg[sz - 1 + k];
	}
	void update(int k, T& v) {// k 番目の値をup(seg[k],v)にする
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
		} else {
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
		} else {
			T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return up(vl, vr);
		}
	}
};

template<typename T>
ll inversion_number(vector<T>& a) {
	ll n = a.size();
	ll res = 0;
	using p = pair<T,int>;
	vector<p> c(n);
	for (int i = 0; i < n; ++i) {
		c[i].first = a[i];
		c[i].second = i;
	}
	sort(c.begin(), c.end());
	SegmentTree<int> st(n, upsum<int>, 0);
	int k = 1;
	for (int i = 0; i < n; ++i) {
		st.update(c[i].second, k);
		res += st.query(c[i].second+1, n);
	}
	return res;
}