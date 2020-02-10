/*
 m進数の四則演算を行うクラス
 順番が逆順なので注意
 最大でm^(INT_MAX+1)-1まで扱える
 m>1,val>0であることが前提で動いている
 四則演算一回あたりの計算量はO(val.size())
*/

class BigInteger{
public:
    int m;
    vector<int> val;//進数の値を格納、n=sum(val[i]*m^i),val[0]=0とval.size()=0がどちらを0とするかが課題
    BigInteger(int _m){//m進数,m>1,将来的にm<-1も対応するかもしれない
        m=_m;
    }
    BigInteger(int _m,int _size){//m進数
        m=_m;
        val.resize(_size);
    }
    void zero_pad(vector<int>& a){//先頭の0を削除,値が0の時が1個だけ残す
        while(a.size()>1&&a.back()==0){
            a.pop_back();
        }
    }
    BigInteger sum(BigInteger d){//m==d.mが前提
        int max_len = max(val.size(),d.val.size());
        BigInteger res(m,max_len);
        int carry=0;
        REP(i,max_len){
            int temp=carry+oor(val.at(i))+oor(d.val.at(i));
            carry=temp/m;
            res.val[i]=temp%m;
        }
        if(carry!=0){
            res.val.push_back(carry);
        }
        return res;
    }
    BigInteger dif(BigInteger d,bool turn_off_zero=false){//m==d.mかつval>d.valが前提,前頭の0を消したいときは第2引数をtrueに
        int max_len = val.size();
        BigInteger res(m,max_len);
        int borrow=0;
        REP(i,max_len){
            int temp=oor(val.at(i))-oor(d.val.at(i))-borrow;
            if(temp<0){
                borrow=1;
                temp+=m;
            }else{
                borrow=0;
            }
            res.val[i]=temp;
        }
        if(turn_off_zero){
            zero_pad(res.val);
        }
        return res;
    }
    BigInteger sum(int d){//m>1が前提
        int len = size();
        BigInteger res(m,len);
        int carry=0;
        REP(i,len){
            int temp=carry+oor(val.at(i))+(d%m);
            d/=m;
            carry=temp/m;
            res.val[i]=temp%m;
        }
        if(carry!=0){
            res.val.push_back(carry);
        }
        return res;
    }
    void sumeq(int d){//m>1が前提
        int len = size();
        int carry=0;
        REP(i,len){
            int temp=carry+oor(val.at(i))+(d%m);
            d/=m;
            carry=temp/m;
            val[i]=temp%m;
        }
        if(carry!=0){
            val.push_back(carry);
        }
        return ;
    }
    BigInteger dif(int d,bool turn_off_zero=false){//val>dが前提,m>1が前提
        int len = val.size();
        BigInteger res(m,len);
        int borrow=0;
        REP(i,len){
            int temp=oor(val.at(i))-d%m-borrow;
            d/=m;
            if(temp<0){
                borrow=1;
                temp+=m;
            }else{
                borrow=0;
            }
            res.val[i]=temp;
        }
        if(turn_off_zero){
            zero_pad(res.val);
        }
        return res;
    }
    void difeq(int d,bool turn_off_zero=false){//val>dが前提,m>1が前提
        int len = val.size();
        int borrow=0;
        REP(i,len){
            int temp=oor(val.at(i))-d%m-borrow;
            d/=m;
            if(temp<0){
                borrow=1;
                temp+=m;
            }else{
                borrow=0;
            }
            val[i]=temp;
        }
        if(turn_off_zero){
            zero_pad(val);
        }
        return ;
    }
    BigInteger pro(int d){
        int max_len = val.size();
        BigInteger res(m,max_len);
        int carry=0;
        REP(i,max_len){
            int temp=val[i]*d+carry;
            carry=temp/m;
            res.val[i]=temp%m;
        }
        while(carry!=0){
            int temp=carry;
            carry=temp/m;
            res.val.push_back(temp%m);
        }
        //zero_pad(res.val);
        return res;
    }
    BigInteger quo(int d){//d!=0が前提
        int max_len = val.size();
        BigInteger res(m,max_len);
        int carry=0;
        for(int i=max_len-1;i>=0;--i){
            int temp=oor(val.at(i))+carry*m;
            carry=temp%d;
            res.val[i]=temp/d;
        }
        //zero_pad(res.val);
        return res;
    }
    bool GREATER(BigInteger d){//m==d.mが前提
        if(size()>d.size()){
            return true;
        }else if(size()<d.size()){
            return false;
        }
        int s = size();
        RREP(i,s){
            if(val[i]>d.val[i]){
                return true;
            }else if(val[i]<d.val[i]){
                return false;
            }
        }
        return false;
    }
    bool GEQ(BigInteger d){//m==d.mが前提
        if(size()>d.size()){
            return true;
        }else if(size()<d.size()){
            return false;
        }
        int s = size();
        RREP(i,s){
            if(val[i]>d.val[i]){
                return true;
            }else if(val[i]<d.val[i]){
                return false;
            }
        }
        return true;
    }
    bool LESS(BigInteger d){//m==d.mが前提
        if(size()>d.size()){
            return true;
        }else if(size()<d.size()){
            return false;
        }
        int s = size();
        RREP(i,s){
            if(val[i]<d.val[i]){
                return true;
            }else if(val[i]>d.val[i]){
                return false;
            }
        }
        return false;
    }
    bool LEQ(BigInteger d){//m==d.mが前提
        if(size()>d.size()){
            return true;
        }else if(size()<d.size()){
            return false;
        }
        int s = size();
        RREP(i,s){
            if(val[i]<d.val[i]){
                return true;
            }else if(val[i]>d.val[i]){
                return false;
            }
        }
        return true;
    }
    bool EQUAL(BigInteger d){//m==d.mが前提
        return GEQ(d)&&LEQ(d);
    }
    BigInteger operator+(BigInteger d){return sum(d);}
    BigInteger operator-(BigInteger d){return dif(d);}
    BigInteger operator+(int d){return sum(d);}
    BigInteger operator-(int d){return dif(d);}
    BigInteger operator*(int d){return pro(d);}
    BigInteger operator/(int d){return quo(d);}
    void operator+=(BigInteger d){val = sum(d).val;}
    void operator-=(BigInteger d){val = dif(d).val;}
    void operator+=(int d){sumeq(d);}
    void operator-=(int d){difeq(d);}
    void operator*=(int d){val = pro(d).val;}
    void operator/=(int d){val = quo(d).val;}
    bool operator>(BigInteger d){return GREATER(d);}
    bool operator<(BigInteger d){return LESS(d);}
    bool operator>=(BigInteger d){return GEQ(d);}
    bool operator<=(BigInteger d){return LEQ(d);}
    bool operator==(BigInteger d){return EQUAL(d);}
    int size(){
        return val.size();
    }
};