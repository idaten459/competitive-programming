/*
gcdライブラリ
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
