/*
 LIS(最長増加部分列)の長さ
 計算量はO(nlogn)
*/

template<typename U>
int lis(vector<U> a,bool broad=true){//broad=true:広義、false:狭義
    int rtn = 0;
    vector<int> lis;
    lis.push_back(a[0]);
    FOR(i,1,a.size()){
        if(broad){
            if(lis.back() <=a [i]){
                lis.push_back(a[i]);
            }else{
                auto itr = upper_bound(all(lis), a[i])-lis.begin();
                lis[itr]=a[i];
            }
        }else{
            if (lis.back() < a[i]) {
                lis.push_back(a[i]);
            }else {
                auto itr = lower_bound(all(lis), a[i]) - lis.begin();
                lis[itr] = a[i];
            }
        }
        
    }
    rtn = lis.size();//LISの長さ
    return rtn;
}
