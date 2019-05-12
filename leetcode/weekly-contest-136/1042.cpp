
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

struct edge{
    int vf = 0;
    int vt = 0;
    array<int, 4> from;
    array<int, 4> to;
    edge(int n){
        REP(i,4){
            from[i] = n;
            to[i] = n;
        }
    }
    int e;
};

bool cmp(const edge &a, const edge &b)
{
    return a.vf+a.vt > b.vf+b.vt;
}

class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        vector<int> rtn(N,0);
        vector<edge> e(N,edge(N));
        Rep(i,N){
            e[i].e = i;
        }
        int l = paths.size();
        REP(i,l){
            int p1 = --paths[i][0];
            int p2 = --paths[i][1];
            e[p1].from[e[p1].vf++] = p2;
            e[p2].from[e[p2].vf++] = p1;
            e[p1].to[e[p1].vt++] = p2;
            e[p2].to[e[p2].vt++] = p1;
        }
        sort(all(e),cmp);
        //rtn[e[0].e] = 1;
        REP(i,N){
            if(rtn[e[i].e]==0){
                bool flag = true;
                REP(j,e[i].vf){
                    if(rtn[e[i].from[j]]==1){
                        flag = false;
                    }
                }
                REP(j,e[i].vt){
                    if(rtn[e[i].to[j]]==1){
                        flag = false;
                    }
                }
                if(flag){
                    rtn[e[i].e] = 1;
                }
            }
        }
        REP(i,N){
            if(rtn[e[i].e]==0){
                bool flag = true;
                REP(j,e[i].vf){
                    if(rtn[e[i].from[j]]==2){
                        flag = false;
                    }
                }
                REP(j,e[i].vt){
                    if(rtn[e[i].to[j]]==2){
                        flag = false;
                    }
                }
                if(flag){
                    rtn[e[i].e] = 2;
                }
                
            }
        }
        REP(i,N){
            if(rtn[e[i].e]==0){
                bool flag = true;
                REP(j,e[i].vf){
                    if(rtn[e[i].from[j]]==3){
                        flag = false;
                    }
                }
                REP(j,e[i].vt){
                    if(rtn[e[i].to[j]]==3){
                        flag = false;
                    }
                }
                if(flag){
                    rtn[e[i].e] = 3;
                }
                
            }
        }
        REP(i,N){
            if(rtn[e[i].e]==0){
                bool flag = true;
                REP(j,e[i].vf){
                    if(rtn[e[i].from[j]]==4){
                        flag = false;
                    }
                }
                REP(j,e[i].vt){
                    if(rtn[e[i].to[j]]==4){
                        flag = false;
                    }
                }
                if(flag){
                    rtn[e[i].e] = 4;
                }
                
            }
        }
        
        return rtn;
    }
};