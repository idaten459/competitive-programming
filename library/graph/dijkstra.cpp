/*
普通のdijkstra
辺の重みが非負であることが条件
計算量はO(|E|log|V|)
pathを与えると、dに頂点sからの最短経路長を格納する。
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_1_A/judge/3899647/C++14
*/

struct edge{
    int to,cost;
    edge(int t,int c){
        to = t;
        cost = c;
    }
};

template<typename T>
void dijkstra(int s,vector<vector<edge>>& path,vector<T>& d){
    priority_queue<P,vector<P>,greater<P>> q;
    q.push(P(0,s));
    d[s] = 0;
    while(!q.empty()){
        P p = q.top();
        q.pop();
        int v = p.second;
        if(d[v]<p.first)continue;
        REP(i,path[v].size()){
            edge e = path[v][i];
            if(d[e.to]>d[v]+e.cost){
                d[e.to]=d[v]+e.cost;
                q.push(P(d[e.to],e.to));
            }
        }
    }
    return ;
}
/*
int main(){
    int n, m, start;
	cin >> n >> m >> start;
	vector<vector<edge>> path(n);
	REP(i, m) {
		int s, t, d;
		cin >> s >> t >> d;
		path[s].push_back(edge(t, d));
	}
	vector<ll> d(n, LLONG_MAX / 2);
	dijkstra(start, path, d);
	REP(i, n) {
		if (d[i] == LLONG_MAX / 2) {
			put("INF");
		} else {
			put(d[i]);
		}
	}
    return 0;
}
*/