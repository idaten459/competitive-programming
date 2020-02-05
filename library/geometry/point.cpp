class point{
public:
    double x,y;
    point(double x,double y):x(x),y(y){}
    point():x(0),y(0){}
    void set(double x,double y){
        this->x = x;
        this->y = y;
    }
    double dist(point p){
        double dx = x-p.x;
        double dy = y-p.y;
        double res = dx*dx+dy*dy;
        res = sqrt(res);
        return res;
    }
    double dist(double x,double y){
        return dist(point(x,y));
    }
    
    double inner_product(point p){
        double res;
        res = x*p.x+y*p.y;
        return res;
    }
    double size(){
        return sqrt(x*x+y*y);
    }
    point norm(){
        return (*this)/size();
    }
    point operator+(point p){
        return point(x+p.x,y+p.y);
    }
    point operator-(point p){
        return point(x-p.x,y-p.y);
    }
    point operator*(double t){
        return point(x*t,y*t);
    }
    double operator*(point p){
        return inner_product(p);
    }
    point operator/(double t){
        return point(x/t,y/t);
    }
    void operator+=(point p){
        x+=p.x;
        y+=p.y;
    }
    void operator-=(point p){
        x-=p.x;
        y-=p.y;
    }
    void operator*=(double t){
        x*=t;
        y*=t;
    }
};

int main(){
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
