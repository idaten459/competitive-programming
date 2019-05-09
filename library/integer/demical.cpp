/*
 bit全探索の一般化みたいなかたち
 10進数のnをk進数で長さlのベクトルを用いて表す関数demicalを用いる。demicalの計算量はO(logN+L)
 abc119cのように何重にもforを回すという表記をこれで帰ることができる
 (demicalする分少し遅いがlogで通らなくらるようではそもそも解法が違う可能性が高い)
 使用例はabc119c2
    この問題の想定解にDFSがあったので他の全探索できないか一考の価値はあると思う
 N=k^lでループを回したい時に用いる
 計算量はO(NlogN)
 
*/
vector<int> demical(ll n,int k,int l){
    vector<int> rtn(l);
    REP(i,l){
        rtn[i]=n%k;
        n/=k;
    }
    //while(n>0){
     //rtn.push_back(n%k);
     //n/=k;
    //}
    return rtn;
}