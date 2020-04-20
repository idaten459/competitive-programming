/*
抽象遅延セグメント木lambda version
モノイドを載せることができる。
upが(区間)更新関数、procが(区間)取得関数、contがupの繰り返し用関数でaddなどの特殊ケースも記述済み
変更が必要な箇所は、up,proc,コンストラクタ呼び出し時の引数(単位元)
単位元は、
add : 0
min : INT_MAX,LLONG_MAX
max : INT_MIN,LLONG_MIN
assign : xに登場しない数(制約に収まる値を単位元にするとやばい)
とするとよさそう
計算量は
構築O(N)
クエリO(logN)
ただし、contがO(logN)かかるやつだとevalがO(log^2N)かかる
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_F/judge/4378677/C++14
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_G/judge/4378723/C++14
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_H/judge/4378733/C++14
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_I/judge/4378744/C++14
*/

template<typename F,typename T>
class Monoid {
public:
	const T unit; // 単位元
	const F f; // 関数
	const int flag;
	Monoid(F f, T unit, int flag = 0) : f(f), unit(unit), flag(flag) {}
};

template<typename Up, typename Proc>
class LazySegmentTree {
public:
	int sz = 1;
	const Up up;		// 更新関数
	const Proc proc;	// 取得関数
	using T = remove_const_t<decltype(up.unit)>; // up関数の型
	vector<T> seg; // セグメント木のデータ配列
	vector<T> lazy; // 遅延評価用の配列
	LazySegmentTree(int n, Up up, Proc proc) : up(up), proc(proc) {
		while (sz < n) sz <<= 1;
		seg.clear();
		lazy.clear();
		seg.resize(sz * 2, proc.unit);
		lazy.resize(sz * 2, up.unit);
	}
	T cont(T& a, int b) { // aをb回procした値
		if (b <= 0)return proc.unit;
		if (b % 2 == 0) {
			T c = cont(a, b / 2);
			return proc.f(c, c);
		} else {
			return proc.f(a, cont(a, b - 1));
		}
		return a;
	}
	T contSum(T& a, int b) { // procが加算のとき
		return a * b;
	}
	T contId(T& a, int b) { // procが繰り返しても同じ値になるもの(max,min,etc...)
		return a;
	}
	void init(std::vector<T> ary) { // aryで初期化する
		const int n = (int)ary.size();
		for (int i = 0; i < n; ++i) {
			set(i, ary[i]);
		}
		for (int i = sz - 2; i >= 0; --i) {
			seg[i] = proc.f(seg[2 * i + 1], seg[2 * i + 2]);
		}
	}
	void init(T a) { // sz個の全要素をaで初期化する
		for (int i = 0; i < sz; ++i) {
			set(i, a);
		}
		for (int i = sz - 2; i >= 0; --i) {
			seg[i] = proc.f(seg[2 * i + 1], seg[2 * i + 2]);
		}
	}
	inline void set(const int& k, const T& x) {// 左からk番目の葉にxを代入する
		seg[sz - 1 + k] = x;
	}

	// k 番目のノードについて遅延評価を行う
	void eval(int k, int l, int r) { // k = [l,r)
		if (lazy[k] != up.unit) {
			int len = r - l;
			if (len > 1) {
				lazy[2 * k + 1] = up.f(lazy[2 * k + 1], lazy[k]);
				lazy[2 * k + 2] = up.f(lazy[2 * k + 2], lazy[k]);
			}
			if (proc.flag == 0) {
				seg[k] = up.f(seg[k], cont(lazy[k], len));
			} else if (proc.flag == 1) {
				seg[k] = up.f(seg[k], contSum(lazy[k], len));
			} else if (proc.flag == 2) {
				seg[k] = up.f(seg[k], contId(lazy[k], len));
			}
			lazy[k] = up.unit;
		}
	}
	void update(int a, int b, T x, int k = 0, int l = 0, int r = -1) { // i in [a,b)に更新up(seg[i],a)を適用
		if (r < 0) r = sz;
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {// 被覆
			lazy[k] = up.f(lazy[k], x);
			eval(k, l, r);
		} else {// 非被覆
			update(a, b, x, 2 * k + 1, l, (l + r) / 2);
			update(a, b, x, 2 * k + 2, (l + r) / 2, r);
			seg[k] = proc.f(seg[2 * k + 1], seg[2 * k + 2]);
		}
	}
	T query(int a, int b, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = sz;
		if (b <= l || r <= a) return proc.unit;
		eval(k, l, r);
		if (a <= l && r <= b) return seg[k];
		T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
		T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
		return proc.f(vl, vr);
	}
};

// 使い方、c++17だとclass templateの型推論が働くのでコメントアウトした方でも動く。
void solve() {
	using type = int64_t;
	auto assign_lambda = [](type& a, type b) {
		return b;
	};
	constexpr type assignUnit = std::numeric_limits<type>::min();
	Monoid<decltype(assign_lambda),decltype(assignUnit)> assign(assign_lambda, assignUnit, 2);
	//Monoid assign(assign_lambda, assignUnit, 2);

	auto sum_lambda = [](type& a, type b) {
		return a + b;
	};
	constexpr type sumUnit = 0;
	Monoid<decltype(sum_lambda), decltype(sumUnit)> sum(sum_lambda, sumUnit, 1);
	//Monoid sum(sum_lambda, sumUnit, 1);

	auto min_lambda = [](type& a, type b) {
		if (a < b)return a;
		return b;
	};
	constexpr type minUnit = numeric_limits<type>::max();
	Monoid<decltype(min_lambda), decltype(minUnit)> intmin(min_lambda, minUnit, 2);
	//Monoid intmin(min_lambda, minUnit, 2);

	auto max_lambda = [](type& a, type b) {
		if (a > b)return a;
		return b;
	};
	constexpr type maxUnit = std::numeric_limits<type>::min();
	Monoid<decltype(max_lambda), decltype(maxUnit)> intmax(max_lambda, maxUnit, 2);
	//Monoid intmax(max_lambda, maxUnit, 2);

	int n, q;
	cin >> n >> q;
	LazySegmentTree<decltype(assign), decltype(sum)> lst(n, assign, sum);
	lst.init(0);
	//LazySegmentTree lst(n, assignt, intmin);
	REP(i, q) {
		int a;
		cin >> a;
		if (a) {
			int s, t;
			cin >> s >> t;
			//s--, t--;
			put(lst.query(s, t + 1));
		} else {
			int s, t, x;
			cin >> s >> t >> x;
			//s--, t--;
			lst.update(s, t + 1, x);
		}

	}
}