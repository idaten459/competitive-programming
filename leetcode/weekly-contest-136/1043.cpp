
#define Rep(i,n) for(int i=0;i<(int)(n);i++)
#define For(i,n1,n2) for(int i=(int)(n1);i<(int)(n2);i++)
#define REP(i,n) for(ll i=0;i<(ll)(n);i++)
#define RREP(i,n) for(ll i=((ll)(n)-1);i>=0;i--)
#define FOR(i,n1,n2) for(ll i=(ll)(n1);i<(ll)(n2);i++)
#define put(a) cout<<a<<"\n"
#define all(a)  (a).begin(),(a).end()
#define SORT(a) sort((a).begin(),(a).end())
#define oorret 0
#define oor(x) [&](){try{x;} catch(const out_of_range& oor){return oorret;} return x;}()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> P;
template<typename T1,typename T2> inline bool chmin(T1 &a,T2 b){if(a>b){a=b;return 1;}return 0;}
template<typename T1,typename T2> inline bool chmax(T1 &a,T2 b){if(a<b){a=b;return 1;}return 0;}

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int rtn = 0;
        int n = A.size();
        vector<int> sum(n,0);
        vector<int> dp(n,0);
        
        //if(n>=K){
            //dp[0] = A[0];
            REP(i,K){
                int temp = 0;
                REP(j,i+1){
                    chmax(temp,A[j]);
                }
                dp[i] = temp*(i+1);
            }
            /*dp[0] = A[0];
            dp[1] = max(A[0],A[1])*2;
            dp[2] = max({A[0],A[1],A[2]})*3;*/
            FOR(i,K,n){
                int temp = 0;
                REP(j,K){
                    int m = 0;
                    REP(l,j+1){
                        chmax(m,A[i-l]);
                    }
                    chmax(temp, dp[i-j-1]+m*(j+1));
                    //dp[i-j-1]+
                }
                /*int t1 = dp[i-3]+max({A[i-2],A[i-1],A[i]})*3;
                int t2 = dp[i-2]+max({A[i-1],A[i]})*2;
                int t3 = dp[i-1]+A[i]*1;*/
                dp[i] = temp;
            }
            return dp.back();
        /*}else{
            return *max_element(all(A))*n;
        }*/
    }
};