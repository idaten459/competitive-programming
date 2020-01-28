/*
渡す関数にラムダ式使ったり、非再帰にしたり色々高速化してみたセグメント木
更新関数upと評価関数evalを別にしてみたり高速化を測ってみました。
Up,Evalはともに
(T& a,T b)を引数にとり、Tを返すことが想定されている
@verify https://atcoder.jp/contests/agc005/submissions/9697352
*/

template<typename T, typename Up, typename Eval>
class SegmentTree{
private:
    const Up up; // 更新関数
    const Eval eval; // 評価関数
    std::vector<T> seg;
public:
    int sz = 1; //　配列長n以上の最小の2冪
    const T unit; // 評価関数の単位元
    explicit SegmentTree(int n,Up&& f,Eval&& g,T unit=0)noexcept:
    up(std::forward<Up>(f)), eval(std::forward<Eval>(g)),unit(unit){
        while (sz < n) sz <<= 1;
        seg.resize(sz * 2, unit);
    }
    explicit SegmentTree(std::vector<T> ary,Up&& f,Eval&& g,T unit=0)noexcept:
    up(std::forward<Up>(f)), eval(std::forward<Eval>(g)), unit(unit){
        const int n = (int)ary.size();
        while (sz < n) sz <<= 1;
        seg.resize(sz * 2, unit);
        init(ary);
    }
    void init(std::vector<T> ary){ // aryで初期化する
        const int n = (int)ary.size();
        for(int64_t i=0;i<n;++i){
            set(i,ary[i]);
        }
        for(int64_t i=sz-2;i>=0;--i){
            eval(seg[2*i+1], seg[2*i+2]);
        }
    }
    void update(int k, T v) {// k番目の値をup(seg[k],v)にする
        k += sz - 1;
        seg[k] = up(seg[k], v);
        while (k > 0) {
            k = (k - 1) / 2;
            seg[k] = eval(seg[2 * k + 1], seg[2 * k + 2]);
        }
    }
    inline void set(const int& k, const T& x) {// 左からk番目の葉にxを代入する
        seg[sz - 1 + k] = x;
    }
    T get(const int& k) {// 左からk番目の葉を得る
        return seg[sz - 1 + k];
    }
    T query_rec(int a, int b) {// [a,b)のupの合成を求める
        int k = 0, l = 0, r = sz;
        return query_rec(a, b, k, l, r);
    }
    T query_rec(int a, int b, int k, int l, int r) {// [a,b)のupの合成を求める(a,b,0,0,sz)のように使う
        if (r <= a || b <= l) {
            return unit;
        }
        if (a <= l && r <= b) {
            return seg[k];
        }
        else {
            T vl = query_rec(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_rec(a, b, k * 2 + 2, (l + r) / 2, r);
            return eval(vl, vr);
        }
    }
    T query(int l,int r){// [l,r)
        l += sz;
        r += sz;
        T res = unit;
        for (;l<r; l>>=1, r>>=1) {
            if(r&1){
                res = eval(seg[--r-1],res);
            }
            if(l&1){
                res = eval(seg[l++-1],res);
            }
        }
        return res;
    }
};

template<typename T,typename Up,typename Eval>
constexpr static inline SegmentTree<T, Up, Eval>
makeSegmentTree(int n,Up&& up,Eval&& eval,T unit=0) noexcept {
    return SegmentTree<T,Up,Eval>(n,std::forward<Up>(up),std::forward<Eval>(eval),unit);
}

template<typename T,typename Up,typename Eval>
constexpr static inline SegmentTree<T, Up, Eval>
makeSegmentTree(std::vector<T> ary,Up&& up,Eval&& eval,T unit=0) noexcept {
    return SegmentTree<T, Up,Eval>(ary,std::forward<Up>(up),std::forward<Eval>(eval),unit);
}

void storage(){
    using type = int;
    auto assign = [](type& a,type b){
        return b;
    };
    
    auto min = [](type& a,type b){
        return std::min<type>(a,b);
    };
    auto max = [](type& a,type b){
        return std::max<type>(a,b);
    };
    auto sum = [](type& a,type b){
        return a+b;
    };
    // SegmentTree<decltype(assign),decltype(min),int> st2(10, std::move(assign), std::move(min), 0);
    //auto st = makeSegmentTree(10,assign,min,0);
    auto st = makeSegmentTree(n,assign,sum,0);
}
