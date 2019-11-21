/*
gcdライブラリ
単位元は0
*/

template<typename T>
T gcd(T u, T v) {
    if(u==0)return v;
    if(v==0)return u;
    T r;
    while (v) {
        r = u % v;
        u = v;
        v = r;
    }
    return u;
}

template<typename T>
T gcd(vector<T> a){
    int l = a.size();
    if(l<=0){
        return 0;
    }else if(l==1){
        return a[0];
    }else{
        T res = gcd(a[0],a[1]);
        FOR(i,2,l){
            res = gcd(res,a[i]);
        }
        return res;
    }
}
