/*
verifyしてない…
辺関連の処理を楽にしようという考え
*/

class ProcGraph {
public:
	struct vertex{
		int index;
		vertex(int ind) :index(ind) {}
	};
	struct edge {
		int index,to,from;
		edge() :to(-1), from(-1), index(-1) {}
		edge(int to, int from, int index) :to(to), from(from), index(index) {}
	};
	vector<vector<edge>> path;
	vector<pair<int, int>> table; // edge index -> (to,from)
	map<pair<int, int>, int> mp; // (to,from) -> edge index
	int n = 0, m = 0;

	ProcGraph(vector<vector<int>>& inputPath) { // 有向グラフ
		n = inputPath.size();
		path.resize(n);
		m = 0;
		for (int i = 0; i < n; ++i) {
			int t = inputPath[i].size();
			path[i].resize(t);
			for (int j = 0; j < t; ++j) {
				pair<int, int> p = { i,inputPath[i][j] };
				table.push_back(p);
				mp[p] = m;
				path[i][j] = edge(inputPath[i][j],i,m++);
			}
		}
	}
	ProcGraph(int n,vector<int>& a, vector<int>& b, bool directed = false) {
		this->n = n;
		m = a.size();
		table.resize(m);
		int count = 0;
		for (int i = 0; i < m; ++i) {
			path[a[i]].push_back(edge(b[i],a[i],count));
			if (!directed) {
				path[b[i]].push_back(edge(a[i], b[i], count));
			}
			pair<int, int> p = { a[i],b[i] };
			table[count] = p;
			mp[p] = count;
			count++;
		}
	}
};

