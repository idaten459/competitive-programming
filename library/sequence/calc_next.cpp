/*
n=|S|とする
next[i][c] := S の i 文字目以降(i文字目を含む)で最初に文字 c が登場する index(登場しない場合はn)
n+2まで確保する理由は(i,n)が知りたいときに+1しながらfor文を回す際に配列外参照しないため
時間計算量はO(n*types)
空間計算量はO(n*types)
文字列ならtypes=26,base='a'
数列ならtypes=10,base='0'
*/

vector<vector<int>> calcNext(const string &S, int types=26, char base='a') {
    int n = (int)S.size();
    vector<vector<int>> res(n + 2, vector<int>(types, n));
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < types; ++j) res[i][j] = res[i+1][j];
        res[i][S[i]-base] = i;
    }
    return res;
}