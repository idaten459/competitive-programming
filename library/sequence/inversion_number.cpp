/*
転倒数を求める
転倒数の定義は、数列{an}に対して、i<j,ai>ajを満たす(i,j)の数
求め方は https://qiita.com/wisteria0410ss/items/296e0daa9e967ca71ed6 を参考にした
i=[0,n)に対して、a[i]の小さい順にseg[i]に1を加えてsegの[i+1,n)の和の合計が転倒数
(st.query(c[i].second+1, n)はc[i].second=kに対して、k<jかつa_K>a_jとなるjの個数)
(旧)
@verify https://atcoder.jp/contests/chokudai_s001/submissions/7132271
        https://atcoder.jp/contests/abc107/submissions/8990727 (<-遅いのが気がかり)
		https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/ALDS1_5_D/judge/3828535/C++14
(新)lambdaセグ木に改修した
@verify https://atcoder.jp/contests/abc107/submissions/9533993
{an}に同じ数が含まれていても正しく動作する
計算量はO(NlogN)
*/

template <typename F, typename T>
class SegmentTree
{
private:
	const F up;
	vector<T> seg;
	int sz = 1;
	T unit;

public:
	explicit SegmentTree(int n, F &&f, T unit = 0) noexcept : up(std::forward<F>(f)), unit(unit)
	{
		while (sz < n)
			sz <<= 1;
		seg.resize(sz * 2, unit);
	}
	void update(int k, T v)
	{ // k 番目の値をup(seg[k],v)にする
		k += sz - 1;
		seg[k] = up(seg[k], v);
		while (k > 0)
		{
			k = (k - 1) / 2;
			seg[k] = up(seg[2 * k + 1], seg[2 * k + 2]);
		}
	}
	void set(const int &k, const T &x)
	{ //左からk番目の葉にxを代入する
		seg[sz - 1 + k] = x;
	}
	T get(const int &k)
	{ //左からk番目の葉を得る
		return seg[sz - 1 + k];
	}
	T query(int a, int b)
	{ //[a,b)のupの合成を求める
		int k = 0, l = 0, r = sz;
		return query(a, b, k, l, r);
	}
	T query(int a, int b, int k, int l, int r)
	{ //[a,b)のupの合成を求める(a,b,0,0,sz)のように使う
		if (r <= a || b <= l)
		{
			return unit;
		}
		if (a <= l && r <= b)
		{
			return seg[k];
		}
		else
		{
			T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return up(vl, vr);
		}
	}
};

template <typename T>
int64_t inversion_number(vector<T> &a)
{ // i<jかつa_i>a_jとなる(i,j)の数
	auto up = [](T &a, T b) {
		return a + b;
	};
	int n = (int)a.size();
	int64_t res = 0;
	using p = pair<T, int>;
	vector<p> c(n);
	for (int i = 0; i < n; ++i)
	{
		c[i].first = a[i];
		c[i].second = i;
	}
	sort(c.begin(), c.end());
	SegmentTree<decltype(up), T> st(n, move(up), 0);
	int k = 1;
	for (int i = 0; i < n; ++i)
	{
		st.update(c[i].second, k);
		res += st.query(c[i].second + 1, n);
	}
	return res;
}
