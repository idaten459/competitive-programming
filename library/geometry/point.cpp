/*
二次元の座標もしくはベクトルを扱うクラス
@verify https://atcoder.jp/contests/arc042/submissions/9916658
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/CGL_1_A/judge/4170511/C++14 (project)
        https://onlinejudge.u-aizu.ac.jp/status/users/idaten/submissions/1/CGL_1_B/judge/4170532/C++14 (reflect)
*/

template<typename T>class point {
public:
	T x, y;
	point(T x, T y) :x(x), y(y) {}
	point() :x(0), y(0) {}
	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}
	T p2dist(point p) { // オーバーフローに注意
		T dx = x - p.x;
		T dy = y - p.y;
		return dx * dx + dy * dy;
	}
	T dist(point p) {
		return sqrt(p2dist(p));
	}
	T dist(T x, T y) {
		return dist(point(x, y));
	}
	T inner_product(point p) { // this・p
		return x * p.x + y * p.y;
	}
	T outer_product(point p) { // this × p
		return x * p.y - y * p.x;
	}
	T cos(point p1, point p2) { // 角度p1,this,p2の余弦
		point t1 = p1 - (*this), t2 = p2 - (*this);
		T ip = t1.inner_product(t2);
		return ip / t1.size() / t2.size();
	}
	T sin(point p1, point p2) { // 角度p1,this,p2の正弦
		point t1 = p1 - (*this), t2 = p2 - (*this);
		T ip = t1.outer_product(t2);
		return ip / t1.size() / t2.size();
	}
	T size() {
		return sqrt(x * x + y * y);
	}
	point norm() {
		return (*this) / size();
	}
	point project(point p1, point p2) { // p1,p2を通る直線へ下ろした垂線の足
		point p3 = p2 - p1;
		T s = p1.p2dist(p2);
		T t = (*this - p1) * p3 / s;
		point res = p3 * t;
		res += p1;
		return res;
	}
	point reflect(point p1, point p2) { // p1,p2を通る直線を軸とした線対称点
		point proj = this->project(p1, p2);
		point p = proj - (*this);
		p *= 2;
		point res = (*this) + p;
		return res;
	}
	T line_dist(point p1, point p2) { // p1,p2を通る直線との距離
		point proj = this->project(p1, p2);
		return this->dist(proj);
	}
	static bool isParallel(point p1, point p2, point p3, point p4) { // p1,p2を通る直線sとp3,p4を通る直線tが平行か
		point s = p2 - p1, t = p4 - p3;
		T op = s.outer_product(t);
		long double eps = 1e-10;
		if (s.size() < eps || t.size() < eps) {
			return false;
		}
		long double si = (long double)op / s.size() / t.size();
		return abs(si) < eps;
	}
	static bool isOrthogonal(point p1, point p2, point p3, point p4) { // p1,p2を通る直線sとp3,p4を通る直線tが垂直か
		point s = p2 - p1, t = p4 - p3;
		T ip = s * t;
		long double eps = 1e-10;
		if (s.size() < eps || t.size() < eps) {
			return false;
		}
		long double co = (long double)ip / s.size() / t.size();
		return abs(co) < eps;
	}
	point operator+(point p) { return point(x + p.x, y + p.y); }
	point operator-(point p) { return point(x - p.x, y - p.y); }
	point operator*(T t) { return point(x * t, y * t); }
	T operator*(point p) { return inner_product(p); }
	point operator/(T t) { return point(x / t, y / t); }
	void operator+=(point p) { x += p.x; y += p.y; }
	void operator-=(point p) { x -= p.x; y -= p.y; }
	void operator*=(T t) { x *= t; y *= t; }
	void operator/=(T t) { x /= t; y /= t; }
	bool operator<(const point& p) const { // 順序付き集合に乗せるために適当に順序付け
		if (p.x == x) {
			return y < p.y;
		} else {
			return x < p.x;
		}
	}
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
