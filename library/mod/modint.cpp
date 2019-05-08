/*
ModIntに対応したpow,fact,combを作ることで、軽量化に成功し、気軽に初期化できるようになった
使用例も一緒に載せてあるので、使い方はmain関数ないを参考されたし
標準入出力に対応
abc042dの「いろはちゃんとます目」で動作確認済み
*/

template<typename T,typename U>
inline T pow(T x,U exp){
    if(exp<=0){
        return 1;
    }
    if(exp%2==0){
        T d = pow(x,exp/2);
        return d*d;
    }
    else{
        return (x*pow(x,exp-1));
    }
}

template<typename T>
inline T fact(T n,vector<T>& table){
    if(n>=(int)table.size()){
        ll s = table.size();
        for(T i=s;i<n+1;++i){
            table.push_back(table.back()*i);
        }
    }
    if(n<0) return 1;
    else return table[n.a];
}

template<typename T>
inline T comb(T n,T m,vector<T>& table){//nCm
    if(n-m<m)return comb(n,n-m,table);
    else return fact(n,table)/fact(m,table)/fact(n-m,table);
}

class ModInt{
public:
    ull a;
    const int mod = 1e9+7;
    ModInt(ull _val=0){
        if(_val>=mod){_val%=mod;}
        a = _val;
    }
    ModInt operator=(const ModInt n){a=n.a;return a;}
    ModInt operator+(const ModInt n){if((a+n.a)>=mod){return a+n.a-mod;}else{return a+n.a;}}
    ModInt operator-(const ModInt n){return a+(-n.a);}
    ModInt operator*(const ModInt n){return a*n.a;}
    ModInt operator/(const ModInt n){return (*this)*pow(n,mod-2);}
    ModInt &operator+=(const ModInt n){(*this)=(*this)+n;return *this;}
    ModInt &operator-=(const ModInt n){(*this)=(*this)-n;return *this;}
    ModInt &operator*=(const ModInt n){(*this)=(*this)*n;return *this;}
    ModInt &operator/=(const ModInt n){(*this)=(*this)/n;return *this;}
    ModInt &operator++(int){(*this)=(*this)+1;return *this;}//前置インクリメントs(++a)のオーバーロード
    ModInt &operator++(){(*this)=(*this)+1;return *this;}//後置インクリメント(a++)のオーバーロード
    ModInt &operator--(int){(*this)=(*this)-1;return *this;}//前置デクリメント(--a)のオーバーロード
    ModInt &operator--(){(*this)=(*this)-1;return *this;}//後置デクリメント(a--)のオーバーロード
    ModInt operator-(){return mod-a;}//単項-演算子(-a)のオーバーロード
    ModInt inv(){ModInt temp(1);return temp/(*this);}//逆数を返す関数 return (*this)/(*this)/(*this);でもいい
    bool operator<(const ModInt n){return a<n.a;}
    bool operator<=(const ModInt n){return a<=n.a;}
    bool operator>(const ModInt n){return a>n.a;}
    bool operator>=(const ModInt n){return a>=n.a;}
    bool operator==(const ModInt n){return a==n.a;}
    //下の関係演算子はpow関数で要請される
    bool operator<(const int n){return a<n;}
    bool operator<=(const int n){return a<=n;}
    bool operator>(const int n){return a>n;}
    bool operator>=(const int n){return a>=n;}
    bool operator==(const int n){return a==n;}
    ModInt operator%(const int n){return a%n;}
};
ostream& operator <<(ostream &o, const ModInt &t) {
    o << t.a;
    return o;
}
istream& operator >>(istream &i,ModInt &t) {
    i >> t.a;
    return i;
}

int main(){
    ModInt h,w,a,b;
    cin >> h >> w >> a >> b;
    vector<ModInt> table(1,1);
    ModInt res;
    for(ModInt i=1;i<h-a+1;++i){
        res += comb(b+i-2,i-1,table)*comb(w-b+h-i-1,h-i,table);
    }
    put(res);
    return 0;
}