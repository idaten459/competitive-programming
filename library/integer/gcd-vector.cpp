/*
vectorの全要素のgcdを求める
gcdもコピペしないと動作しない
*/
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