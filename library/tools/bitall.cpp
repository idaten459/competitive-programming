/*
bit全探索を行うライブラリ
計算量はO(n*2^n)
*/
void bitall(){
    vector<int> a = {0,1,2,3};
    ll n = a.size();
    for(ll bit = 0; bit < (1<<n); ++bit){
        vector<ll> s;
        for(ll i = 0; i < n; ++i){
            if(((bit>>i) & 1) == 1){
                //処理部分
                s.push_back(a[i]);
            }
        }
        cout << "[ ";
        for(int i=0;i<s.size();++i){
            cout << s[i] << " ";
        }
        cout << "]\n";
    }
}