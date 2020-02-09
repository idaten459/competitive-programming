/*
二次元の座標もしくはベクトルを扱うクラス
@verify https://atcoder.jp/contests/arc042/submissions/9916658
*/

template<typename T>class point{
public:
    T x,y;
    point(T x,T y):x(x),y(y){}
    point():x(0),y(0){}
    void set(T x,T y){
        this->x = x;
        this->y = y;
    }
    T p2dist(point p){
        T dx = x-p.x;
        T dy = y-p.y;
        return dx*dx+dy*dy;
    }
    T dist(point p){
        return sqrt(p2dist(p));
    }
    T dist(T x,T y){
        return dist(point(x,y));
    }
    T inner_product(point p){ // this・p
        return x*p.x+y*p.y;
    }
    T outer_product(point p){ // this × p
        return x*p.y-y*p.x;
    }
    T cos(point p1,point p2){ // 角度p1,this,p2の余弦
        point t1 = p1-(*this),t2 = p2-(*this);
        T ip = t1.inner_product(t2);
        return ip/t1.size()/t2.size();
    }
    T sin(point p1,point p2){ // 角度p1,this,p2の正弦
        point t1 = p1-(*this),t2 = p2-(*this);
        T ip = t1.outer_product(t2);
        return ip/t1.size()/t2.size();
    }
    T size(){
        return sqrt(x*x+y*y);
    }
    point norm(){
        return (*this)/size();
    }
    point project(point p1,point p2){ // p1,p2を通る直線へ下ろした垂線の足
        point p3 = p2-p1;
        T s = p1.p2dist(p2);
        T t = (*this-p1)*p3/s;
        point res = p3*t;
        res+=p1;
        return res;
    }
    T line_dist(point p1,point p2){ // p1,p2を通る直線との距離
        point proj = this->project(p1, p2);
        return this->dist(proj);
    }
    point operator+(point p){return point(x+p.x,y+p.y);}
    point operator-(point p){return point(x-p.x,y-p.y);}
    point operator*(T t){return point(x*t,y*t);}
    T operator*(point p){return inner_product(p);}
    point operator/(T t){return point(x/t,y/t);}
    void operator+=(point p){x+=p.x;y+=p.y;}
    void operator-=(point p){x-=p.x;y-=p.y;}
    void operator*=(T t){x*=t;y*=t;}
    void operator/=(T t){x/=t;y/=t;}
};

int main(){
    using point = point<double>;
    int n;
    double px,py;
    cin >> px >> py;
    point p(px,py);
    
    cin >> n;
    vector<point> x(n);
    REP(i,n){
        double tx,ty;
        cin >> tx >> ty;
        x[i].set(tx,ty);
    }
    double res = -1;
    REP(i,n){
        point x1 = x[i];
        point x2 = x[(i+1)%n];
        point t1 = x2-x1;
        point t2 = p-x1;
        double t3 = t1*t2/t1.size();
        point x3 = t1.norm()*t3+x1;
        double tmp = (p-x3).size();
        if(res<0){
            res = tmp;
        }else{
            chmin(res,tmp);
        }
    }
    cout << setprecision(20) << res << endl;
    return 0;
}
