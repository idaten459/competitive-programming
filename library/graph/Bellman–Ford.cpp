/*
 ベルマンフォード法
 負のコストがある単一始点の最短距離を導出する
 solve 閉路を考慮しない最短距離と負閉路があるかO(|V||E|)
 restore solveで計算した経路からendに向かう最短経路の復元(ある一つのみ)
 最長経路(正閉路)を導出したい際は、costを-1倍するとよい
 @verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_1_B/judge/3916106/C++14
*/

class BellmanFord {
public:
	struct edge {
		int to;
		ll cost;
		edge(int to, ll cost) : to(to), cost(cost) {}
	};
	struct node {
		int from;
		ll cost;
		bool neg;
		node(int from, ll cost) : from(from), cost(cost) {
			neg = false;
		}
	};
	vector<vector<edge>> path;
	int n;
	ll inf = LLONG_MAX / 2;

	BellmanFord(int n) :n(n) {
		path.resize(n);
	}
	void push_edge(int a, int b, ll c) {
		path[a].push_back(edge(b, c));
	}
	vector<node> solve(int start) {
		vector<node> dist(n, node(-1, inf));
		dist[start].cost = 0;
		REP(i, this->n - 1) {
			REP(j, this->n) {
				REP(k, path[j].size()) {
					if (dist[j].cost != this->inf) {
						if (chmin(dist[path[j][k].to].cost, dist[j].cost + path[j][k].cost)) {
							dist[path[j][k].to].from = j;
						}
					}
				}
			}
		}
		REP(i, n) {
			REP(j, path[i].size()) {
				int from = i;
				int to = path[i][j].to;
				ll cost = path[i][j].cost;
				if (dist[to].cost != this->inf && dist[from].cost + cost < dist[to].cost) {
					dist[to].cost = dist[from].cost + cost;
					dist[to].neg = true;
				}
				if (dist[from].neg) {
					dist[to].neg = true;
				}
			}
		}
		return dist;
	}
	vector<int> restore(vector<node>& dist, int end) {
		vector<int> res;
		if (dist[end].neg || dist[end].cost == this->inf) {
			return res;
		} else {
			int now = end;
			while (now >= 0) {
				res.push_back(now);
				now = dist[now].from;
			}
			reverse(res.begin(), res.end());
			return res;

		}
	}
};

int main() {
	IOS;
	int n, m, r;
	cin >> n >> m >> r;
	vector<ll> a(m), b(m), c(m);
	BellmanFord bf(n);
	REP(i, m) {
		cin >> a[i] >> b[i] >> c[i];
		//a[i]--;
		//b[i]--;
		bf.push_edge(a[i], b[i], c[i]);
	}
	int start = r;
	auto dist = bf.solve(start);
	REP(i, n) {
		int end = i;
		if (dist[end].neg) {
			put("NEGATIVE CYCLE");
			return 0;
		}
	}
	REP(i, n) {
		int end = i;
		if (dist[end].cost == bf.inf) {
			put("INF");
		} else {
			put(dist[end].cost);
			//put(bf.restore(dist, end));
		}
		
	}
	return 0;
}
