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
    int k;
    cin >> k;
    vector<vector<edge>> p(k);
    REP(i,k){
        int temp = i*10%k;
        p[i].push_back(edge(temp,0));
        p[i].push_back(edge((i+1)%k,1));
    }
    vector<int> d(k,INT_MAX/2);
    int s = 1;
    dijkstra(s, p, d);
    put(d[0]+1);
    return 0;
}
*/