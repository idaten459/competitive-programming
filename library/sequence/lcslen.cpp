/*
LCS(最長共通部分列)のlcs長
vectorを引数にとる
stringではlcs-stringを参照
計算量はO(st)
*/
template<typename T>
int lcslen(vector<T>& s,vector<T>& t){
    ll ls = s.size();
    ll lt = t.size();
    vector<vector<int>> lcs(ls+1,vector<int>(lt+1,0));
    REP(i,ls+1){
        REP(j,lt+1){
            if(i==0||j==0){
                lcs[i][j]=0;
            }else{
                if(s[i-1]==t[j-1]){
                    lcs[i][j]=lcs[i-1][j-1]+1;
                }else{
                    lcs[i][j]=max(lcs[i-1][j],lcs[i][j-1]);
                }
            }
        }
    }
    return lcs[ls][lt];
}