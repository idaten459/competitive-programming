// 単位元を-1とする自然数のmin関数
template<typename T> inline T min(T a, T b) {
	if (a == -1) return b;
	if (b == -1) return a;
	if (a > b) {
		return b;
	}
	return a;
}