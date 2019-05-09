/*
lis(最長増加部分列)の復元
計算量はO(NlogN)
*/
template<typename T>
vector<T> lis_vec(vector<T> a){
    vector<int> lis;
    lis.push_back(a[0]);
    FOR(i,1,a.size()){
        if(lis.back()<=a[i]){
            lis.push_back(a[i]);
        }else{
            auto itr = lower_bound(all(lis), a[i])-lis.begin();
            lis[itr]=a[i];
        }
    }
    lis.push_back(INT_MAX);
    ll m = lis.size();
    deque<int> dq;
    for(ll i=n-1;0<=i;--i){
        if(m>1){
            if(lis[m-2]<=a[i]&&a[i]<=lis[m-1]){
                dq.push_front(a[i]);
                m--;
            }
        }
    }
    vector<T> rtn;
    for(auto a:dq){
        rtn.push_back(a);
    }
    return rtn;
}