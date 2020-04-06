/*
素因数分解をするライブラリ
計算量はO(√n)
vector<piar>の形式で返し、firstが素数、secondeが指数
n=1の時に注意
*/
template<class T> inline vector<pair<T,int>> factoring(T n){
    using p = pair<T,int>;
    using vp = vector<p>;
    vp res;
    T k = n;
    if(n%2==0){
        res.push_back(p(2,1));
        n/=2;
        while (n%2==0) {
            res[0].second++;
            n/=2;
        }
    }
    for(T i=3;i<=n&&i*i<=k;i+=2){
        if(n%i==0){
            res.push_back(p(i,1));
            n/=i;
            while (n%i==0) {
                res.back().second++;
                n/=i;
            }
        }
    }
    if(n!=1){
        res.push_back(p(n,1));
    }
    return res;
}
