template<typename T>
vector<int> Coordinate_compression(vector<T>& a){
    int n = a.size();
    map<T,int> mp;
    Rep(i,n){
        mp[a[i]] = 0;
    }
    int cnt = 0;
    for(auto v:mp){
        mp[v.first] = cnt++;
    }
    vector<int> res(n);
    REP(i,n){
        res[i] = mp[a[i]];
    }
    return res;
}

/*
verify at https://atcoder.jp/contests/abc036/submissions/5538430
*/