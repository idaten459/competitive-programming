/*
二次元累積和を計算するライブラリ
区間res[i][j] = (k,l) \in [(0,0),(i,j))におけるa[k][l]の総和を全ての(i,j)においてO(hw)で求める
restore_cum_sumは[(i,j),(k,l))の総和をO(1)で求める
@verify https://atcoder.jp/contests/arc025/submissions/9360462
*/
template<typename T, typename U>
vector<vector<T>> cumulative_sum(vector<vector<U>>& a) {
	if (a.size() == 0)return vector<vector<T>>(1, vector<T>(1, 0));
	int h = a.size(), w = a[0].size();
	vector<vector<T>> res(h + 1, vector<T>(w + 1, 0));
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			res[i + 1][j + 1] = res[i + 1][j] + a[i][j];
		}
	}
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w + 1; ++j) {
			res[i + 1][j] += res[i][j];
		}
	}
	return res;
}

template<typename T>
T restore_cum_sum(vector<vector<T>>& s,int i,int j,int k,int l) { 
	T res = s[k][l] - s[k][j] - s[i][l] + s[i][j];
	return res;
}
