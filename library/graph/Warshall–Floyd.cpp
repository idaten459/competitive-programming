/*
 ワーシャルフロイド法
 ver 0.0.0
 グラフの全二点間の最短距離を求める
 無向グラフ入力のためa[i]とb[i]をひっくり返したものも距離にとってる
 頂点数をnとすると(一般にはV)
 計算量はO(n^3)
 経路復元も計算量はO(n^3)
 経路復元の参考サイト↓
 http://zeosutt.hatenablog.com/entry/2015/05/05/045943
 利用例abc51d(経路の辺を求めている)
 ver 1.0.0
 関数化して、AOJでverifyを確認した
 @verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/GRL_1_C/judge/4405336/C++14 ver 1.0.0
*/

template<typename T>
vector<vector<T>> WarshalFloyd(vector<vector<T>>& path,T inf) {
    int n = path.size();
    vector<vector<T>> res = path;
    vector<vector<int>> next(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        res[i][i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            next[i][j] = j;
        }
    }
    // Warshal Floyd
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                if (res[i][k] != inf && res[k][j] != inf && (res[i][j] == inf || res[i][j] > res[i][k] + res[k][j])) {
                    res[i][j] = res[i][k] + res[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    bool negative_cycle = false;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                if (res[i][k] != inf && res[k][j] != inf && (res[i][j] == inf || res[i][j] > res[i][k] + res[k][j])) {
                    negative_cycle = true;
                    res[i][j] = -inf;
                }
                if (res[i][k] == -inf || res[k][j] == -inf) {
                    res[i][j] = -inf;
                }
            }
        }
    }
    // iからjへの経路を復元
    /*vector<vector<vector<int>>> res(n, vector<vector<int>>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            for (int cur = i; cur != j; cur = next[cur][j]) {
                res.push_back(cur);
            }
        }
    }*/
    return res;
}