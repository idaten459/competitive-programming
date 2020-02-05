/*
三角形の色々を扱うライブラリ
obtuse,right,orthocenterは確認してない
内心、外心はmain関数のような方法で合っているか確認した。
外心について、int入力とかで、一直線上にあるとnanが帰ってきて面倒なので、obtuseで場合わけするとよさそう
三角形の内部に点が含まれるかとかも実装したい
@verify https://atcoder.jp/contests/abc151/submissions/9917005 (外心と距離と一応obtuse)
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

template<typename T>
class triangle{
public:
    using point = point<T>;
    point p1,p2,p3;
    array<point,3> p;
    triangle(point p1,point p2,point p3):p1(p1),p2(p2),p3(p3){
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
    }
    void set(point p1,point p2,point p3){
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
    }
    T area(){
        point t1 = p[1]-p[0],t2 = p[2]-p[0];
        T res = t1.outer_product(t2);
        res = abs(res);
        return res;
    }
    int obtuse(){ // 鈍角の頂点番号を返す(0-indexed)、鋭角三角形の場合-1
        for(int i=0;i<3;++i){
            point t1 = p[(1+i)%3]-p[i], t2 = p[(2+i)%3]-p[i];
            T ip = t1*t2;
            if(ip<0){
                return i;
            }
        }
        return -1;
    }
    int right(T eps=1e-9){ // 直角の頂点番号を返す(0-indexed)、鋭角三角形の場合-1
        for(int i=0;i<3;++i){
            point t1 = p[(1+i)%3]-p[i], t2 = p[(2+i)%3]-p[i];
            T ip = t1*t2;
            if(abs(ip)<eps){
                return i;
            }
        }
        return -1;
    }
    point gravity_center(){ // 重心
        point res = p[0]+p[1]+p[2];
        res /= 3;
        return res;
    }
    point inner_center(){ // 内心
        point res;
        T d1,d2,d3;
        d1 = p[1].dist(p[2]);
        d2 = p[2].dist(p[0]);
        d3 = p[0].dist(p[1]);
        res = p[0]*d1+p[1]*d2+p[2]*d3;
        res/=d1+d2+d3;
        return res;
    }
    T inscribed_circle_diameter(){ // 内接円の半径
        point ic = inner_center();
        T res = ic.line_dist(p[0], p[1]);
        return res;
    }
    point circumcenter(){ // 外心
        point res;
        T s1,s2,s3;
        s1 = 2*p[0].sin(p[1], p[2])*p[0].cos(p[1],p[2]);
        s2 = 2*p[1].sin(p[2], p[0])*p[1].cos(p[2],p[0]);
        s3 = 2*p[2].sin(p[0], p[1])*p[2].cos(p[0],p[1]);;
        res = p[0]*s1+p[1]*s2+p[2]*s3;
        res/= s1+s2+s3;
        return res;
    }
    T circumradius(){ // 外接円の半径
        point cc = circumcenter();
        T res = cc.dist(p[0]);
        return res;
    }
    point orthocenter(){ // 垂心(verifyしてない)
        point res;
        T icd = inscribed_circle_diameter();
        T c = p[0].cos(p[1],p[2]);
        point d = p[0].project(p[1],p[2]);
        point ah = d.norm()*icd*c*2;
        res = p[0]+ah;
        return res;
    }
};


int main(){
    using point = point<double>;
    using triangle = triangle<double>;
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_real_distribution<> dist1(-100.0, 100.0);
    double eps = 1e-9;
    int loop = 100000;
    REP(i,loop){
        vector<point> p(3);
        REP(j,3){
            p[j] = point(dist1(engine),dist1(engine));
        }
        triangle t(p[0],p[1],p[2]);
        point cc = t.circumcenter();
        vector<double> d(3);
        REP(j,3){
            d[j] = cc.dist(p[j]);
        }
        REP(j,3){
            REP(k,3){
                if(d[j]-d[k]>eps&&(d[j]-d[k])/d[j]>eps){
                    cout << "circumcenter" << endl;
                }
            }
        }
        point ic = t.inner_center();
        vector<double> d2(3);
        REP(j,3){
            d2[j] = ic.line_dist(p[(j+1)%3],p[(j+2)%3]);
        }
        REP(j,3){
            REP(k,3){
                if(d[j]-d[k]>eps&&(d[j]-d[k])/d[j]>eps){
                    cout << "inner_center" << endl;
                }
            }
        }
    }
    return 0;
}
