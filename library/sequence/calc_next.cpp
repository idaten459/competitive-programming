/*
n=|S|とする
next[i][c] := S の i 文字目以降(i文字目を含む)で最初に文字 c が登場する index(登場しない場合はn)
計算量はO(n)
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