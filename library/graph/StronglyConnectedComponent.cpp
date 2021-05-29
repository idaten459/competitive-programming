/*
 強連結成分分解
 隣接リストを引数とし，強連結成分同士が等しい値が格納された配列を返す
 計算量は，O(V+E)
 @verify https://atcoder.jp/contests/typical90/submissions/22987237
*/

void dfs(vector<vector<int>>& path, vector<bool>& visited, vector<int>& post_order, int v) {
    visited[v] = true;
    for (int i = 0; i < path[v].size(); i++) {
        if (!visited[path[v][i]]) {
            dfs(path, visited, post_order, path[v][i]);
        }
    }
    post_order.push_back(v);
}

void reverse_dfs(vector<vector<int>>& reverse_path, vector<bool>& visited, vector<int>& comp, int v, int k) {
    visited[v] = true;
    comp[v] = k;
    for (int i = 0; i < reverse_path[v].size(); i++) {
        if (!visited[reverse_path[v][i]]) {
            reverse_dfs(reverse_path, visited, comp, reverse_path[v][i], k);
        }
    }
}

vector<int> StronglyConnectedComponent(vector<vector<int>>& path) {
    int n = path.size();
    vector<int> res(n, -1);
    vector<vector<int>> reverse_path(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < path[i].size(); j++) {
            reverse_path[path[i][j]].push_back(i);
        }
    }
    vector<bool> visited(n, false);
    vector<int> post_order;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(path, visited, post_order,i);
        }
    }
    reverse(post_order.begin(), post_order.end());
    std::fill(all(visited), false);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[post_order[i]]) {
            reverse_dfs(reverse_path, visited, res, post_order[i], k++);
        }
    }
    return res;
}