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
        node(int from, ll cost) : from(from), cost(cost) {}
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
        REP(i, this->n - 1) {
            REP(j, this->n) {
                REP(k, path[j].size()) {
                    int from = j;
                    int to = path[j][k].to;
                    ll cost = path[j][k].cost;
                    if (dist[to].cost != this->inf && dist[from].cost + cost < dist[to].cost) {
                        dist[to].cost = -this->inf;
                    }
                    if (dist[from].cost==-this->inf) {
                        dist[to].cost = -this->inf;
                    }
                }
            }
        }
        return dist;
    }
    vector<int> restore(vector<node>& dist, int end) {
        vector<int> res;
        if (dist[end].cost == -this->inf || dist[end].cost == this->inf) {
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
    int n, m, p;
    cin >> n >> m >> p;
    vector<ll> a(m), b(m), c(m);
    BellmanFord bf(n);
    REP(i, m) {
        cin >> a[i] >> b[i] >> c[i];
        a[i]--;
        b[i]--;
        bf.push_edge(a[i], b[i], -(c[i] - p));
    }
    int start = 0, end = n - 1;
    auto dist = bf.solve(start);
    if (dist[end].cost==-bf.inf) {
        put(-1);
    } else {
        put(max(-dist[end].cost, 0ll));
    }
    return 0;
}

