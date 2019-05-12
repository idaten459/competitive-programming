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
    bool isRobotBounded(string instructions) {
        bool rtn;
        int dir = 0;
        int dx[] = {0,-1,0,1};
        int dy[] = {1,0,-1,0};
        P now = P(0,0);
        for(int i=0;i<instructions.size();++i){
            if(instructions[i]=='R'){
                dir--;
                if(dir<0){
                    dir+=4;
                }
            }
            if(instructions[i]=='L'){
                dir++;
                if(dir>=4){
                    dir-=4;
                }
            }
            if(instructions[i]=='G'){
                now.first += dx[dir];
                now.second += dy[dir];
            }
        }
        if((now.second!=0||now.first!=0)&&dir==0){
            rtn = false;
        }else{
            rtn = true;
        }
        return rtn;
    }
};