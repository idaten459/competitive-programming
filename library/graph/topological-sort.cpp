/*
トポロジカルソート
DAG（有向非巡回グラフ)の各ノードを有向辺の順序を保ったまま並べる関数
pathは、隣接リストで、そのグラフが自己ループなしのDAGであることと正しくソートできる(正しくソートできないときはそのグラフが閉路を持つということ)
グラフ全体で弱連結でなくても動作する(極論一つの辺がなくても動作するのが実装を見るとわかる)
計算量はO(V+E)
res!=path.size()だとpathが閉路をもつ
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_4_B/judge/3815022/C++14 (AOJ)
*/

vector<int> topologicalSort(vector<vector<int>>& path){
    int n = (int)path.size();
    vector<int> res;
    vector<int> entry(n,0);
    queue<int> q;
    for(int i=0;i<n;++i){
        for(int j=0;j<path[i].size();++j){
            entry[path[i][j]]++;
        }
    }
    for(int i=0;i<n;++i){
        if(!entry[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int p = q.front();
        q.pop();
        res.push_back(p);
        for(int i=0;i<path[p].size();++i){
            if(--entry[path[p][i]]==0){
                q.push(path[p][i]);
            }
        }
    }
    return res;
}
