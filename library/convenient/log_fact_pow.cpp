/*
巨大数を桁数だけで扱うときに役立つ関数二つ
*/

double logfact(int n,vector<double>& table){
    if(table[n]>=0){
        return table[n];
    }
    double res = (double)log10(n)+logfact(n-1,table);
    table[n] = res;
    return res;
}

double logpow(int n,int m){
    return (double)m*log10(n);
}