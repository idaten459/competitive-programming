//2次元配列の転置
template <typename T>
vector<vector<T>> trans_vec(vector<vector<T>> &a){
    assert(a.size());
    int n = a.size(),m = a[0].size();
    vector<vector<T>> res(m,vector<T>(n));
    REP(i,n){
        REP(j,m){
            res[j][i]=a[i][j];
        }
    }
    return res;
}