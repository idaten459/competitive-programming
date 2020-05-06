/*
無向グラフの最小全域木を求めるライブラリ。
Kruskal法では、fromとtoは区別がないので反転して追加する必要はない。
Kruskal法を用いて計算量はO(MlogM)
unionfindを用いるので、コピペ用に一緒に載せておく
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_2_A/judge/3959179/C++14
*/

class UnionFind {
private:
	vector<int> par, height, size;
public:
	UnionFind(int n) {
		par.resize(n);
		for (int i = 0; i < n; ++i) {
			par[i] = i;
		}
		height.resize(n, 0);
		size.resize(n, 1);
	}
	int root(int x) {
		if (par[x] == x) {
			return x;
		} else {
			par[x] = root(par[x]);
			return par[x];
		}
	}
	bool same(int x, int y) {
		return root(x) == root(y);
	}
	void unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y)return;
		if (height[x] < height[y]) {
			par[x] = y;
			size[y] += size[x];
		} else {
			par[y] = x;
			size[x] += size[y];
			if (height[x] == height[y])height[x]++;
		}
	}
	int cnt(int x) {
		x = root(x);
		return size[x];
	}
};

template<typename T>
class MinimumSpanningTree {
private:
	vector<int> from, to;
	vector<pair<T, int>> cost;
	int n, m;
public:
	MinimumSpanningTree<T>(vector<int>& from, vector<int>& to, vector<T>& cost, int n) : from(from), to(to), n(n) {
		this->m = (int)cost.size();
		this->cost.resize(m);
		for (int i = 0; i < m; ++i) {
			this->cost[i].first = cost[i];
			this->cost[i].second = i;
		}
		sort(this->cost.begin(), this->cost.end());
	}
	vector<int> Kruskal() {
		vector<int> res; //mstを構成するindexの集合
		UnionFind uf(this->n);
		for (int i = 0; i < this->m; ++i) {
			int index = this->cost[i].second;
			if (!uf.same(this->from[index], this->to[index])) {
				res.push_back(index);
				uf.unite(this->from[index], this->to[index]);
			}
			if (res.size() == n - 1) {
				break;
			}
		}
		return res;
	}
};
