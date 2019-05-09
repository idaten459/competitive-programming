/*
 行列のクラスと繰り返し二乗法を用いて二項間漸化式を求める
 計算量は、O(H*W*logN)
 使用例はyp786でフィボナッチ数列を解いている
 f_{n+2}=a*f_{n+1}+b*f_nを変形して、
 (f_n+2)=(a b)*(f_n+1)
 (f_n+1) (1 0) (f_n  )
 とすると
 (f_n+1)=(a b)^n*(f_1)
 (f_n  ) (1 0)   (f_0)
 となるから、これを解くことで、f_nを得る
*/

int n;

class Matrix{
public:
    vector<vector<ll>> m;
    int height,width;
    Matrix(int h,int w){//sizeを指定
        height = h;
        width = w;
        m.resize(h);
        REP(i,h){
            m[i].resize(w);
        }
    }
    Matrix operator*(Matrix b){
        int h=height;
        int w=b.width;
        int n=width;
        //if(n!=b.height){
        //}d
        Matrix c(h,w);
        REP(i,h){
            REP(j,w){
                ll v=0;
                REP(k,n){
                    v+=m[i][k]*b.m[k][j];
                }
                c.m[i][j]=v;
            }
        }
        return c;
    }
    Matrix operator*(ll x){
        Matrix c(height,width);
        c.m=m;
        REP(i,height)REP(j,width)c.m[i][j]*=x;
        return c;
    }
    Matrix operator+(Matrix b){//大きさが同じことが前提
        Matrix c(height,width);
        REP(i,height)REP(j,width)c.m[i][j]=m[i][j]+b.m[i][j];
        return c;
    }
    Matrix operator-(Matrix b){
        Matrix c(height,width);
        REP(i,height)REP(j,width)c.m[i][j]=m[i][j]-b.m[i][j];
        return c;
    }
    void operator*=(ll x){
        REP(i,height)REP(j,width)m[i][j]*=x;
    }
    
};


Matrix pow_mat(Matrix a,int k){
    if(k==1){
        return a;
    }
    if(k%2==0){
        return pow_mat(a,k/2)*pow_mat(a,k/2);
    }else{
        return pow_mat(a,k-1)*a;
    }
}

int main(){
    cin >> n;
    Matrix A(2,2);
    ll f0 = 2;
    ll f1 = 1;
    ll a = 1;
    ll b = 1;
    A.m[0][0]=a;
    A.m[0][1]=b;
    A.m[1][0]=1;
    A.m[1][1]=0;
    
    Matrix res(2,2);
    res = pow_mat(A,n);
    ll fn = res.m[1][0]*f1+res.m[1][1]*f0;
    put(fn);
    return 0;
}