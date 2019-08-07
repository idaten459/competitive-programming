/*
splaytreeという平衡二分探索木の一種
search,insert,erase,find_orderを木のnode数をnとしてamortized O(logn)で行える
node数の最大値をNとして空間計算量はO(N)でk番目の値を得るデータ構造としてはかなり少ない
定数倍が重いので10^6のクエリはこなせない(AOJ:https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/ALDS1_4_C/judge/3795855/C++14)チューニングすればギリいけそうな秒数ではあるが
@verified
https://atcoder.jp/contests/arc033/submissions/6437113

*/

template<typename T>
class SplayTree{//insert,erase based
public:
    struct node_t{
        node_t *cp[2];
        node_t *pp;
        T val;
        int key;
        int size;
        T sum;
        node_t(T v,int k):cp{nullptr,nullptr},pp(nullptr),val(v),key(k),size(1),sum(val){}
    };
    node_t* root;
    SplayTree():root(nullptr){}
    int count(node_t *t){
        return !t ? 0 : t->size;
    }
    int sum(node_t *t){
        return !t ? 0 : t->sum;
    }
    node_t *update(node_t *t){
        t->size = 1 + count(t->cp[0]) + count(t->cp[1]);
        t->sum = t->val + sum(t->cp[0]) + sum(t->cp[1]);
        //t-> = std::min({min(t->cp[0]), t->key, min(t->co[1])});
        return t;
    }
    node_t *rotate(node_t *t,int b){//{0,1}={left,right}rot
        assert(t!=nullptr);
        node_t *s = t->cp[1-b];// 1-bは子の左右反転
        node_t *p = t->pp;
        if(s){
            s->pp = t->pp;
            if(!p){
                this->root = s;
            }else{
                int lr = p->cp[1]==t;
                p->cp[lr] = s;
            }
            t->cp[1-b]=s->cp[b];
            if(s->cp[b])s->cp[b]->pp = t;
            s->cp[b]=t;
            t->pp = s;
            update(t);
            update(s);
        }else{// tが回転したい方に子を持たない場合
            return t;
        }
        return s;//回転した部分木の根を返す
    }
    node_t *zig(node_t *t){//int bを渡した方が良い？
        assert(t->pp!=nullptr);
        node_t *p = t->pp;
        int lr = p->cp[0]==t;
        return rotate(p,lr);
    }
    node_t *zigzig(node_t *t,int b){
        assert(t->pp!=nullptr);
        assert(t->pp->pp!=nullptr);
        node_t *p = t->pp;
        node_t *gp = p->pp;
        zig(p);
        return zig(t);
    }
    node_t *zigzag(node_t *t,int b){
        assert(t->pp!=nullptr);
        assert(t->pp->pp!=nullptr);
        node_t *p = t->pp;
        node_t *gp = p->pp;
        zig(t);
        return zig(t);//return tは自明なのでなんか冗長な気がする
    }
    bool is_root(node_t *t){
        return !t->pp&&t!=nullptr;
    }
    node_t *splay(node_t *t){//bugってる
        while(!is_root(t)){
            node_t *p = t->pp;
            if(is_root(p)){
                t = zig(t);
            }else{
                node_t *gp = p->pp;
                int b[2];
                b[0] = p->cp[1]==t;
                b[1] = gp->cp[1]==p;
                if(b[0]==b[1]){
                    zigzig(t, b[0]);
                }else{
                    zigzag(t, b[0]);
                }
            }
        }
        return root;
    }
    bool is_leaf(node_t *t){
        return !t->cp[0]&&!t->cp[1];
    }
    node_t *search(int k){//keyがkのnodeを返す、存在しない場合はnullptrを返す。直近でアクセスしたnodeでsplayする
        node_t *x = this->root,*y;
        if(!x)return nullptr;
        while (x!=nullptr) {
            y=x;
            if(k<x->key){
                x = x->cp[0];
            }else if(k>x->key){
                x = x->cp[1];
            }else{
                break;
            }
        }
        splay(y);
        return x;
        /*node_t *q = this->root;
        while(q!=nullptr&&k!=q->key){
            if(q->key>k){
                q = q->cp[0];
            }else{
                q = q->cp[1];
            }
        }
        return q;*/
    }
    node_t *insert(T v,int k){
        node_t *x = root;
        node_t *y = nullptr;
        node_t *z = new node_t(v,k);
        if(z==nullptr)exit(2);
        if(!x){//rootがnullptrだった場合は、rootの更新処理をする
            x = z;
            this->root=x;
            return x;
        }
        while (true) {
            y=x;
            if(z->key<x->key){
                if(x->cp[0]){
                    x=x->cp[0];
                }else{
                    z->pp = x;
                    x->cp[0] = z;
                    //x=x->cp[0];
                    break;
                }
            }else if(z->key>x->key){
                if(x->cp[1]){
                    x=x->cp[1];
                }else{
                    z->pp = x;
                    x->cp[1] = z;
                    //x=x->cp[1];
                    break;
                }
            }else{
                return x;//同じkeyの場合、更新するか保持するか迷いどころ
            }
        }
        while(y!=nullptr){
            update(y);
            y = y->pp;
        }
        return splay(z);
    }
    node_t *erase(node_t *t){//tが木に属していることが前提
        splay(t);
        if(!t->cp[0]&&!t->cp[1]){//q->size==1,左右の子ノードが無いとき
            this->root = nullptr;
            delete t;
            t = nullptr;
            return nullptr;
        }else if(!t->cp[0]){//右の子ノードのみある場合
            this->root = t->cp[1];
            t->cp[1]->pp=nullptr;
            delete t;
            t=nullptr;
            return root;
        }else if(!t->cp[1]){
            this->root = t->cp[0];
            t->cp[0]->pp=nullptr;
            delete t;
            t=nullptr;
            return this->root;
        }else{
            node_t *x=t->cp[0],*y;
            while(x!=nullptr){
                y = x;
                x = x->cp[1];
            }
            splay(y);
            node_t* p = t->pp;
            int b = (p->cp[1]==t);
            if(t->cp[1]){
                t->cp[1]->pp = p;
                p->cp[b] = t->cp[1];
            }else{
                p->cp[b] = nullptr;
            }
            delete t;
            t = nullptr;
            while(p!=nullptr){
                update(p);
                p = p->pp;
            }
            return y;
        }
    }
    node_t *erase(int k){//keyがkのnodeを消去
        node_t *t = search(k);
        return erase(t);
    }
    node_t *find_order(node_t *t,int k){//keyがk番目(0-indexed)のnodeを返す
        if(!t)return t;//kがtree全体のサイズより大きい場合や負の場合はnullptrを返す
        int c = count(t->cp[0]);
        if(k==c){
            return t;
        }else if(k<c){
            return find_order(t->cp[0], k);
        }else{
            return find_order(t->cp[1], k-c-1);
        }
    }
};
