/*
lcmを求めるライブラリ
単位元は1
計算量はlog(u+v)
*/

template<typename T>
ll lcm(T u,T v){
    ll res = (ll)u/gcd(u,v);
    res*= v;
    return res;
}

template<typename T>
T lcm(vector<T> a){
    int l = a.size();
    if(l<=0){
        return 1;
    }else if(l==1){
        return a[0];
    }else{
        T res = lcm(a[0],a[1]);
        FOR(i,2,l){
            res = lcm(res,a[i]);
        }
        return res;
    }
}