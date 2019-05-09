/*
 LIS(最長増加部分列(の長さ
 計算量はO(nlogn)
*/

template<typename T,typename U>
T lis(vector<U> a){
    T rtn = 0;
    vector<int> lis;
    lis.push_back(a[0]);
    FOR(i,1,a.size()){
        if(lis.back()<=a[i]){
            lis.push_back(a[i]);
        }else{
            auto itr = upper_bound(all(lis), a[i])-lis.begin();
            lis[itr]=a[i];
        }
    }
    rtn = lis.size();//LISの長さ
    return rtn;
}
