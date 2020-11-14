/*
普通のdijkstra
辺の重みが非負であることが条件
計算量はO(|E|log|V|)
pathを与えると、dに頂点sからの最短経路長を格納する。
T=intの時にoverflowに注意
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_1_A/judge/3899647/C++14
*/

template<typename T>
struct edge{
    int to;
    T cost;
    edge(int t,T c){
        to = t;
        cost = c;
    }
};

template<typename T>
void dijkstra(int s,vector<vector<edge<T>>>& path,vector<T>& d){
    using pi = pair<T,int>;
    priority_queue<pi,vector<pi>,greater<pi>> q;
    q.push(pi(0,s));
    d[s] = 0;
    while(!q.empty()){
        pi p = q.top();
        q.pop();
        int v = p.second;
        if(d[v]<p.first)continue;
        REP(i,path[v].size()){
            edge<T> e = path[v][i];
            if(d[e.to]>d[v]+e.cost){
                d[e.to]=d[v]+e.cost;
                q.push(pi(d[e.to],e.to));
            }
        }
    }
    return ;
}

/*
int main(){
    int n, m, start;
	cin >> n >> m >> start;
	vector<vector<edge<ll>>> path(n);
	REP(i, m) {
		int s, t, d;
		cin >> s >> t >> d;
		path[s].push_back(edge<ll>(t, d));
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
