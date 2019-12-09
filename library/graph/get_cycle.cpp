/*
手元環境でN=100,m=n*10,loop=1000で反例が見つからなかったのでコーナーケースがなければ正しそう
get_cycleは有向グラフのpathを与えると、閉路が存在した場合ある閉路を一つ返す関数
計算量はO(NM)
@verify https://atcoder.jp/contests/abc142/submissions/8888296
*/

void find_cycle(vector<vector<int>>& path, int v, int p, stack<int>& st, vector<int>& vis, vector<int>& cycle) {
	if (cycle.size() > 0)return;
	for (int i = 0; i < path[v].size(); ++i) {
		if (vis[path[v][i]] == 1) {
			if (cycle.size() == 0) {
				cycle.push_back(v);
				while (!st.empty() && st.top() != path[v][i]) {
					cycle.push_back(st.top());
					st.pop();
				}
				cycle.push_back(path[v][i]);
				reverse(cycle.begin(), cycle.end());
			}
			return;
		} else if (vis[path[v][i]] == 0) {
			vis[path[v][i]] = 1;
			st.push(v);
			find_cycle(path, path[v][i], v, st, vis, cycle);
			vis[path[v][i]] = 2;
			if (!st.empty())st.pop();
		}
	}
	return;
}

vector<int> get_cycle(vector<vector<int>>& path) { // n=100,m=n*10,loop=1000で反例が見つからなかった下手なジャッジより回したのでコーナーさえなければOK
	int n = path.size();
	vector<int> vis(n, 0);
	vector<int> cycle;
	REP(i, n) {
		if (vis[i] == 0) {
			vis[i] = 1;
			stack<int> st;
			find_cycle(path, i, -1, st, vis, cycle);
			vis[i] = 2;
		}
		if (cycle.size() > 0) {
			return cycle;
		}
	}
	return cycle;
}
