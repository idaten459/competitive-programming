template<typename T>
T up(const T& l, const T& r) {//SegmentTreeのupdate関数
	T res;
	res.first = l.first * r.first;
	res.second = l.second * r.first + r.second;
	return res;
}

template<typename T>
class SegmentTree {
public:
	vector<T> seg;
	int sz = 1;
	T unit;
	//T (*up)(const T& l,const T& r);
	SegmentTree(int n, T unit = 0) {
		this->unit = unit;
		//int sz = 1;
		while (sz < n) sz <<= 1;
		seg.resize(sz * 2, unit);
		//up = &up1;
	}
	void set(const int& k, const T& x) {//左からk番目の葉にxを代入する
		seg[sz - 1 + k] = x;
	}
	T get(const int& k) {//左からk番目の葉を得る
		return seg[sz - 1 + k];
	}
	void update(int k, const T& v) {// k 番目の値をvに変更
		k += sz - 1;
		seg[k] = v;
		while (k > 0) {
			k = (k - 1) / 2;
			seg[k] = up(seg[2 * k + 1], seg[2 * k + 2]);
		}
	}
	T query(int a, int b, int k, int l,int r) {//[a,b)のupの合成を求める(a,b,0,0,sz)のように使う
		if (r <= a || b <= l) {
			return unit;
		}
		if (a <= l && r <= b) {
			return seg[k];
		}
		else {
			T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return up(vl, vr);
		}
	}
};

/*
verified at 
- https://atcoder.jp/contests/arc008/submissions/5539259
- https://atcoder.jp/contests/abc125/submissions/me
*/