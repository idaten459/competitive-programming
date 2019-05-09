/*
 ワーシャルフロイド法
 グラフの全二点間の最短距離を求める
 無向グラフ入力のためa[i]とb[i]をひっくり返したものも距離にとってる
 頂点数をnとすると(一般にはV)
 計算量はO(n^3)
 経路復元も計算量はO(n^3)
 経路復元の参考サイト↓
 http://zeosutt.hatenablog.com/entry/2015/05/05/045943
 利用例abc51d(経路の辺を求めている)
*/

int n,m;

int main(){
    cin >> n >> m;
    vector<vector<int>> e(n,vector<int>(n,1e6));//infで初期化
    //vector<vector<int>> inv(n,vector<int>(n,1e6));//辺を求めるための配列
    vector<int> a(m);
    vector<int> b(m);
    vector<int> c(m);
    REP(i,m){
        cin >> a[i] >> b[i] >> c[i];
        --a[i];
        --b[i];
        e[a[i]][b[i]] = c[i];
        e[b[i]][a[i]] = c[i];//無向グラフ
        inv[a[i]][b[i]]=i;
        inv[b[i]][a[i]]=i;
    }
    REP(i,n){
        e[i][i]=0;
    }
 
    vector<vector<int>> next(n,vector<int>(n,0));//頂点の遷移情報を記録
    //vector<int> used(m,0);
    REP(i,n){
        REP(j,n){
            next[i][j] = j;
        }
    }
    //ワーシャルフロイド法
    REP(k,n){
        REP(i,n){
            REP(j,n){
                if(chmin(e[i][j],e[i][k]+e[k][j])){
                    next[i][j]=next[i][k];
                }
            }
        }
    }
    //iからjへの経路を復元
    REP(i,n){
        REP(j,n){
            for(int cur=i;cur!=j;cur=next[cur][j]){
                printf("%d",cur);
            }
            printf("%d\n",j);
        }
    }
    return 0;
}