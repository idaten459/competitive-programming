/*
[部分列 DP --- 文字列の部分文字列を重複なく走査する DP の特集](https://qiita.com/drken/items/a207e5ae3ea2cf17f4bd)
next[i][c]  := Sのi文字目以降([i,n))で最初に文字cが登場するindex
[i,n)か(i,n)かが毎回わからなくなる and 毎回ググってコピペするのでここに保存しておく
当然ながら大文字なら'A'をひく
計算量はO(26*n)
*/

vector<vector<int>> calcNext(const string &S) {
    int n = (int)S.size();
    vector<vector<int> > res(n+1, vector<int>(26, n));
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) res[i][j] = res[i+1][j];
        res[i][S[i]-'a'] = i;
    }
    return res;
}
