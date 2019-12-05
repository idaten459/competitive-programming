/*
最大流を求めるアルゴリズム
dinic法(蟻本p.194~195)
計算量はO(N^2 M)だが実際はこれよりも早く動作するらしい
一般グラフで、
孤立点がない場合に|最大マッチング|+|最小辺カバー|=|V|
|最大安定集合(最大独立集合)|+|最小点カバー|=|V|(NP困難)
二部グラフの場合に|最大マッチング|=|最小点カバー|
が成り立つ。
これはverifyしてないが、おなじs,tで追加辺があるならpathそのままでやった方が早い
なんなら追加、削除、変更をメソッドとして書いてもいいのでは(変更: https://onlinejudge.u-aizu.ac.jp/problems/2313)
@verify https://atcoder.jp/contests/soundhound2018/submissions/8716332  グリッドグラフを二部グラフに変換している
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_6_A/judge/4017623/C++14 最大流
		https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_7_A/judge/4018165/C++14 二部マッチング
*/

class flow {
public:
	struct edge {
		int to, rev; // 行先、逆辺
		ll cap; // 容量
		edge(int to, ll cap, int rev) :to(to), cap(cap), rev(rev) {}
	};
	vector<vector<edge>> path;
	vector<int> level, iter; // sからの距離、どこまで調べたか
	int numv; // 辺の本数
	flow(int n) {// n辺
		this->numv = 0;
		this->path.resize(n);
		this->level .resize(n);
		this->iter.resize(n);
	}
	void add_edge(int from, int to, ll cap) {
		this->path[from].push_back(edge(to, cap, this->path[to].size()));
		this->path[to].push_back(edge(from, 0, this->path[from].size() - 1)); // 逆辺
		this->numv++;
	}
	void dist(int s) {
		fill(this->level.begin(), this->level.end(), -1);
		this->bfs(s);
	}
	void bfs(int s) { // sからの最短距離計算
		queue<int> q;
		q.push(s);
		this->level[s] = 0;
		while (!q.empty()) {
			int p = q.front();
			q.pop();
			for (int i = 0; i < this->path[p].size(); ++i) {
				edge& e = this->path[p][i];
				if (e.cap > 0 && this->level[e.to] < 0) {
					this->level[e.to] = this->level[p] + 1;
					q.push(e.to);
				}
			}
		}
	}
	ll inc_path(int v, int t, ll f) { // 増加パスをDFSで探す
		fill(this->iter.begin(), this->iter.end(), 0);
		return dfs(v, t, f);
	}
	ll dfs(int v, int t, ll f) {
		if (v == t)return f;
		for (int& i = this->iter[v]; i < this->path[v].size(); ++i) {
			edge& e = this->path[v][i];
			if (e.cap > 0 && this->level[v] < this->level[e.to]) {
				ll d = this->dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					this->path[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
	ll max_flow(int s, int t) { // sからtへの最大流を計算
		ll flow_value = 0;
		while (true) {
			this->dist(s);
			if (this->level[t] < 0)return flow_value;
			ll f;
			while ((f = this->inc_path(s, t, 10)) > 0) {
				flow_value += f;
			}
		}
	}
};