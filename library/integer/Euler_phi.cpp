/*
オイラーのファイ関数
1以上n以下でnと互いに素な整数の個数を返す
互いに素とは2数の整数の最大公約数が1のことを指すので、phi(1)=1に注意
計算量はfactoringがボトルネックで、O(sqrt(n))
*/

template<class T> inline vector<pair<T, int>> factoring(T n) {
	using p = pair<T, int>;
	using vp = vector<p>;
	vp res;
	T k = n;
	if (n % 2 == 0) {
		res.push_back(p(2, 1));
		n /= 2;
		while (n % 2 == 0) {
			res[0].second++;
			n /= 2;
		}
	}
	for (T i = 3; i <= n && i * i <= k; i += 2) {
		if (n % i == 0) {
			res.push_back(p(i, 1));
			n /= i;
			while (n % i == 0) {
				res.back().second++;
				n /= i;
			}
		}
	}
	if (n != 1) {
		res.push_back(p(n, 1));
	}
	return res;
}

namespace {
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

	template<typename T> inline T phi(T n) {
		vector<pair<T, int>> fact = factoring(n);
		T res = 1;
		const int l = (int)fact.size();
		for (int i = 0; i < l; ++i) {
			T tmp = pow<T>(fact[i].first, fact[i].second - 1);
			res *= (tmp * fact[i].first - tmp);
		}
		return res;
	}
}