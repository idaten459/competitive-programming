/*
lcmを求めるライブラリ
単位元は1
計算量はlog(u+v)
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


template<typename T, typename U>
long long lcm(T u, U v) {
	long long res = (long long)u / gcd(u, v);
	res *= v;
	return res;
}

template<typename T>
long long lcm(vector<T> a) {
	int l = a.size();
	long long res = 1;
	for (int i = 0; i < l; ++i) {
		res = lcm(res, a[i]);
	}
	return res;
}