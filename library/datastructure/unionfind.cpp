class UnionFind {
private:
	vector<int> par, height, size;
	int ele;
public:
	UnionFind(int n) {
		par.resize(n);
		REP(i, n) {
			par[i] = i;
		}
		height.resize(n, 0);
		size.resize(n, 1);
		ele = n;
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
		ele--;
		if (height[x] < height[y]) {
			par[x] = y;
			size[y] += size[x];
		} else {
			par[y] = x;
			size[x] += size[y];
			if (height[x] == height[y])height[x]++;
		}
	}
	int get_size(int x) {
		x = root(x);
		return size[x];
	}
	int get_ele() {
		return ele;
	}
};