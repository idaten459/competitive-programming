/*
 約数の列挙(昇順)を行う
 計算量はO(√N)
*/

template<typename T>
vector<T> divisor(T n){
    vector<T> res1;
    vector<T> res2;
    
    for(T i=1;i*i<=n;i++){
        if(n%i==0){
            res1.push_back(i);
            if(i!=n/i){
                res2.push_back(n/i);
            }
            
        }
    }
    RREP(i,res2.size()){
        res1.push_back(res2[i]);
    }
    return res1;
}