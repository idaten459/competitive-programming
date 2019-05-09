string lcs(string& s,string& t){
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
    string res = "";
    ll ms=ls;
    ll mt=lt;
    while(lcs[ms][mt]!=0){
        if(s[ms-1]==t[mt-1]){
            res.push_back(s[ms-1]);
            ms--;mt--;
        }else if(lcs[ms-1][mt]>=lcs[ms][mt-1]){
            ms--;
        }else{
            mt--;
        }
    }
    reverse(all(res));
    return res;
}