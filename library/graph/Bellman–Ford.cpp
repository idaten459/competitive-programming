/*
 ベルマンフォード法
 負のコストがある単一始点の最短距離を導出する
 下は実装が始点:src=0,終点:n-1になっている
 「終点」を含む負閉路が存在する場合は"inf"を出力している(2n周している)<-2周する必要なくない?←有向グラフだと2週要る
 どこかに負閉路が存在することを確かめるにはn周でいい？ただしflag=trueのところのifは外すこと
 計算量はO(V*E)
 使用例はabc061d
*/

int n,m;

int main(){
    cin >> n >> m;
    vector<int> a(m);
    vector<int> b(m);
    vector<ll> c(m);
    REP(i,m){
        cin >> a[i] >> b[i] >> c[i];
        --a[i];
        --b[i];
    }
    //Bellman-Ford法
    vector<ll> dist(n,1e15);
    int src = 0;
    dist[src]=0;
    REP(i,n*2){
        bool flag = false;
        REP(j,m){
            if(chmin(dist[b[j]],dist[a[j]]+c[j])){
                if(b[j]==n-1)flag = true;
            }
        }
        if(i==2*n-1&&flag){
            put("inf");
            return 0;
        }
    }
    put(dist.back());
    return 0;
}