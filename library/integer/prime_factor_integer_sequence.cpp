/*
連続する整数の素因数分解、区間篩みたいな感じ
計算量はd=r-l,としてO(d logd + sqrt(r)loglog r)
@vefity https://atcoder.jp/contests/jag2017autumn/submissions/12236928
*/

template<typename T>
T sqrtInt(T n, bool flag = true) {
	T ok = 0, ng = 0;
	if (flag) {
		ng = n;
		while (abs<T>(ng - ok) > 1) {
			T mid = (ng + ok) / 2;
			if (mid * mid > n) {
				ng = mid;
			} else {
				ok = mid;
			}
		}
	} else {
		ok = n;
		while (abs<T>(ok - ng) > 1) {
			T mid = (ng + ok) / 2;
			if (mid * mid < n) {
				ng = mid;
			} else {
				ok = mid;
			}
		}
	}
	return ok;
}

vector<vector<int64_t>> prime_factor(int64_t l, int64_t r) { // [l,r)
	using i64 = int64_t;
	i64 d = r - l;
	i64 sqr = sqrtInt(r) + 1;
	vector<vector<i64>> pf(d);
	vector<i64> rem(d);
	for (i64 i = l; i < r; ++i) {
		rem[i - l] = i;
	}
	vector<i64> vir(sqr, -1);
	for (i64 i = 2; i < sqr; ++i) {
		if (vir[i] < 0) {
			vir[i] = i;
			for (i64 j = i * i; j < sqr; j += i) {
				if (vir[j] < 0) {
					vir[j] = i;
				}
			}
			for (i64 j = (l + i - 1) / i * i; j < r; j += i) {
				while (rem[j - l] % i == 0) {
					rem[j - l] /= i;
					pf[j - l].push_back(i);
				}
			}
		}
	}
	for (i64 i = l; i < r; ++i) {
		if (rem[i - l] > 1) {
			pf[i - l].push_back(rem[i - l]);
		}
	}
	return pf;
}