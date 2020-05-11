/*
ver 0.0.0 :
渡す関数にラムダ式使ったり、非再帰にしたり色々高速化してみたセグメント木
更新関数upと評価関数evalを別にしてみたり高速化を測ってみました。
Up,Evalはともに
(T& a,T b)を引数にとり、Tを返すことが想定されている
ver 1.0.0 :
致命的なバグを修正した(交換則を前提としてしまっていた)
ver 1.0.1 :
init(T num)のバグを修正
@verify https://atcoder.jp/contests/agc005/submissions/9697352 (ver 0.0.0)
        https://atcoder.jp/contests/arc008/submissions/12288271 (ver 1.0.0)
*/

template<typename T, typename Up, typename Eval>
class SegmentTree {
private:
	const Up up; // 更新関数
	const Eval eval; // 評価関数
	std::vector<T> seg;
public:
	int sz = 1; //　配列長n以上の最小の2冪
	const T unit; // 評価関数の単位元
	explicit SegmentTree(int n, Up f, Eval g, T unit = 0)noexcept :
		up(f), eval(g), unit(unit) {
		while (sz < n) sz <<= 1;
		seg.resize(sz * 2, unit);
	}
	void init(std::vector<T>& ary) { // aryで初期化する
		const int n = (int)ary.size();
		for (int64_t i = 0; i < n; ++i) {
			set(i, ary[i]);
		}
		for (int64_t i = sz - 2; i >= 0; --i) {
			seg[i] = eval(seg[2 * i + 1], seg[2 * i + 2]);
		}
	}
	void init(T num) { // sz個の全要素をaで初期化する
		for (int64_t i = 0; i < sz; ++i) {
			set(i, num);
		}
		for (int64_t i = sz - 2; i >= 0; --i) {
			seg[i] = eval(seg[2 * i + 1], seg[2 * i + 2]);
		}
	}
	void update(int k, T v) {// k番目の値をup(seg[k],v)にする
		k += sz - 1;
		seg[k] = up(seg[k], v);
		while (k > 0) {
			k = (k - 1) / 2;
			seg[k] = eval(seg[2 * k + 1], seg[2 * k + 2]);
		}
	}
	inline void set(const int& k, const T& x) { // 左からk番目の葉にxを代入する(更新はしない)
		seg[sz - 1 + k] = x;
	}
	T get(const int& k) { // 左からk番目の葉を得る
		return seg[sz - 1 + k];
	}
	T query(int l, int r) { // eval[l,r)
		l += sz;
		r += sz;
		T resl = unit, resr = unit;
		for (; l < r; l >>= 1, r >>= 1) {
			if (r & 1) {
				resr = eval(seg[--r - 1], resr);
			}
			if (l & 1) {
				resl = eval(seg[l++ - 1], resl);
			}
		}
		T res = eval(resl, resr);
		return res;
	}
};

void storage(){
    using type = int;
    auto assign = [](type& a,type b){
        return b;
    };
    constexpr type assignUnit = std::numeric_limits<type>::min();
	
    auto min = [](type& a,type b){
        return std::min<type>(a,b);
    };
    constexpr type minUnit = std::numeric_limits<type>::max();

	auto max = [](type& a,type b){
        return std::max<type>(a,b);
    };
    constexpr type maxUnit = std::numeric_limits<type>::min();

	auto sum = [](type& a,type b){
        return a+b;
    };
    constexpr type sumUnit = 0;
	int sz=10;
    SegmentTree<type,decltype(assign),decltype(min)> st(sz, assign, min, minUnit);
    //SegmentTree st2(sz, assign, min, minUnit); // c++17
    //auto st = makeSegmentTree(10,assign,min,0);
    //auto st = makeSegmentTree(n,assign,sum,0);
}
