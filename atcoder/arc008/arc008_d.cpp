#include "bits/stdc++.h"
using namespace std;
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

typedef pair<double,double> pd;

template<typename T>
vector<int> Coordinate_compression(vector<T>& a){
    int n = a.size();
    map<T,int> mp;
    Rep(i,n){
        mp[a[i]] = 0;
    }
    int cnt = 0;
    for(auto v:mp){
        mp[v.first] = cnt++;
    }
    vector<int> res(n);
    REP(i,n){
        res[i] = mp[a[i]];
    }
    return res;
}

template<typename T>
T up(const T& l,const T& r){//SegmentTreeのupdate関数
    T res;
    res.first = l.first*r.first;
    res.second = l.first*r.second+l.second;
    return res;
}

template<typename T>
class SegmentTree{
public:
    vector<T> seg;
    int sz = 1;
    T unit;
    //T (*up)(const T& l,const T& r);
    SegmentTree(int n,T unit=0){
        this->unit = unit;
        int sz = 1;
        while(sz<n) sz <<= 1;
        seg.resize(sz*2,unit);
        //up = &up1;
    }
    void set(const int& k,const T& x){//左からk番目の葉にxを代入する
        seg[sz-1+k] = x;
    }
    T get(const int& k){//左からk番目の葉を得る
        return seg[sz-1+k];
    }
    void update(int k,const T& v){//k番目の値をvに変更
        k+=sz-1;
        seg[k] = v;
        while(k>0){
            k = (k-1)/2;
            seg[k] = up(seg[2*k+1], seg[2*k+2]);
        }
    }
    T query(int a,int b,int k,int l,int r){//[a,b)のupの合成を求める
        if(r<=a||b<=l){
            return unit;
        }
        if(a<=l&&r<=b){
            return seg[k];
        }else{
            int vl = query(a,b,k*2+1,l,(l+r)/2);
            int vr = query(a,b,k*2+2,(l+r)/2,r);
            return up(vl,vr);
        }
    }
};

int main(){
    ll n;
    int m;
    cin >> n >> m;
    vector<ll> p(m);
    vector<pd> a(m);
    
    Rep(i,m){
        cin >> p[i] >> a[i].first >> a[i].second;
    }
    vector<int> ord = Coordinate_compression(p);
    
    SegmentTree<pd> st(m,pd(1,0));
    double resmax = 1;
    double resmin = 1;
    Rep(i,m){
        st.update(ord[i], a[i]);
        pd d = st.seg[0];
        double temp = d.first+d.second;
        chmax(resmax,temp);
        chmin(resmin,temp);
    }
    cout << setprecision(20);
    put(resmin);
    put(resmax);
    return 0;
}

