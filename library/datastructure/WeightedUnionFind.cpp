//使用例は、arc094d people on a line、計算量はo(α(n))

template<typename W>
class WeightedUnionFind{
private:
    vector<int> par,height,size;
    vector<W> dif_w;
public:
    WeightedUnionFind(int n,W unit=0){
        par.resize(n);
        REP(i,n){
            par[i] = i;
        }
        height.resize(n,0);
        size.resize(n,1);
        dif_w.resize(n,unit);
    }
    int root(int x){
        if(par[x]==x){
            return x;
        }else{
            int r = root(par[x]);
            dif_w[x] += dif_w[par[x]];
            return par[x] = r;
        }
    }
    bool same(int x,int y){
        return root(x)==root(y);
    }
    bool unite(int x,int y,W w){
        w += weight(x);
        w -= weight(y);
        x = root(x);
        y = root(y);
        if(x==y)return false;
        if(height[x]<height[y]){
            par[x]=y;
            size[y]+=size[x];
            dif_w[x] = -w;
        }else{
            par[y]=x;
            size[x]+=size[y];
            dif_w[y] = w;
            if(height[x]==height[y])height[x]++;
        }
        return true;
    }
    int cnt(int x){
        x=root(x);
        return size[x];
    }
    W weight(int x){
        root(x);
        return dif_w[x];
    }
    W dif(int x,int y){//y-x
        return weight(y)-weight(x);
    }
};