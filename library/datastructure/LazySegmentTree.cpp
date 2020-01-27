/*
抽象遅延セグメント木
モノイドを載せることができる。
upが(区間)更新関数、procが(区間)取得関数、contがupの繰り返し用関数でaddなどの特殊ケースも記述済み
変更が必要な箇所は、up,proc,コンストラクタ呼び出し時の引数(単位元)
単位元は、
add : 0
min : INT_MAX,LLONG_MAX
max : INT_MIN,LLONG_MIN
assign : xに登場しない数(制約に収まる値を単位元にするとやばい)
とするとよさそう
計算量は
構築O(N)
クエリO(logN)
ただし、contがO(logN)かかるやつだとevalがO(log^2N)かかる
@verify https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_F/judge/4135585/C++14
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_G/judge/4135582/C++14
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_H/judge/4135567/C++14
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/DSL_2_I/judge/4135607/C++14
        https://yukicoder.me/submissions/421995
*/

template<typename T>
class LazySegmentTree{
public:
    int sz = 1;
    int contFlag;
    T elemUp; // upの単位元
    T elemPr; // procの単位元
    vector<T> seg; // セグメント木のデータ配列
    vector<T> lazy; // 遅延評価用の配列
    T up(T& a,T b){ // 更新関数
        if(b==elemUp)return a;
        if(a==elemUp)return b;
        return a+b; // 加算
        //return b; // 代入
    }
    T proc(T& a,T b){ // 評価関数
        if(b==elemPr)return a;
        if(a==elemPr)return b;
        //if(a>b)return a;// max
        //return b;
        if(a<b)return a;// min
        return b;
        //return a+b; // 加算
    }
    T cont(T& a,int b){ // aをb回procした値
        if(b<=0)return elemPr;
        if(b%2==0){
            T c = cont(a,b/2);
            return proc(c,c);
        }else{
            return proc(a,cont(a,b-1));
        }
        return a;
    }
    T contSum(T& a,int b){ // procが加算のとき
        return a*b;
    }
    T contId(T& a,int b){ // procが繰り返しても同じ値になるもの(max,min,etc...)
        return a;
    }
    LazySegmentTree(int n,T ep=0,T eu=0,int cf=0):elemPr(ep),elemUp(eu),contFlag(cf){
        while (sz < n) sz <<= 1;
        seg.clear();
        lazy.clear();
        seg.resize(sz * 2, elemPr);
        lazy.resize(sz * 2, elemUp);
    }
    void init(std::vector<T> ary){ // aryで初期化する
        const int n = (int)ary.size();
        for(int i=0;i<n;++i){
            set(i,ary[i]);
        }
        for(int i=sz-2;i>=0;--i){
            seg[i] = proc(seg[2*i+1], seg[2*i+2]);
        }
    }
    void init(T a){ // sz個の全要素をaで初期化する
        for(int i=0;i<sz;++i){
            set(i,a);
        }
        for(int i=sz-2;i>=0;--i){
            seg[i] = proc(seg[2*i+1], seg[2*i+2]);
        }
    }
    inline void set(const int& k, const T& x) {// 左からk番目の葉にxを代入する
        seg[sz - 1 + k] = x;
    }
    
    // k 番目のノードについて遅延評価を行う
    void eval(int k, int l, int r) { // k = [l,r)
        if(lazy[k] != elemUp) {
            int len = r-l;
            if(len > 1){
                lazy[2*k+1] = up(lazy[2*k+1],lazy[k]);
                lazy[2*k+2] = up(lazy[2*k+2],lazy[k]);
            }
            if(contFlag==0){
                seg[k] = up(seg[k],cont(lazy[k],len));
            }else if(contFlag==1){
                seg[k] = up(seg[k],contSum(lazy[k],len));
            }else if(contFlag==2){
                seg[k] = up(seg[k],contId(lazy[k],len));
            }
            lazy[k] = elemUp;
        }
    }
    void update(int a,int b,T x,int k=0,int l=0,int r=-1){ // i in [a,b)に更新up(seg[i],a)を適用
        if(r < 0) r = sz;
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b){// 被覆
            lazy[k] = up(lazy[k],x);
            eval(k, l, r);
        }else{// 非被覆
            update(a, b, x, 2*k+1, l, (l+r)/2);
            update(a, b, x, 2*k+2, (l+r)/2, r);
            seg[k] = proc(seg[2*k+1], seg[2*k+2]);
        }
    }
    T query(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = sz;
        if(b <= l || r <= a) return elemPr;
        eval(k, l, r);
        if(a <= l && r <= b) return seg[k];
        T vl = query(a, b, 2*k+1, l, (l+r)/2);
        T vr = query(a, b, 2*k+2, (l+r)/2, r);
        return proc(vl, vr);
    }
};

int main(){
    int n,q;
    cin >> n >> q;
    LazySegmentTree<int> lst(n,0,0);
    REP(i,q){
        int que;
        cin >> que;
        if(que==0){
            int s,t,x;
            cin >> s >> t >> x;
            lst.update(s-1,t,x);
        }else{
            int j;
            cin >> j;
            put(lst.query(j-1,j));
        }
    }
    return 0;
}
