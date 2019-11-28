/*
gcdライブラリ
単位元は0
*/

template<typename T, typename U>
T gcd(T u, U v) {
	if (u == 0)return v;
	if (v == 0)return u;
	T r;
	while (v) {
		r = u % v;
		u = v;
		v = r;
	}
	return u;
}

template<typename T>
T gcd(vector<T> a) {
	int l = a.size();
	T res = 0;
	for (int i = 0; i < l; ++i) {
		res = gcd(res, a[i]);
	}
	return res;
}
