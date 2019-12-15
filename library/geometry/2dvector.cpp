/*
Tはllか、double,long doubleを想定
==はTがllを想定
平面幾何をベクトルで扱うとき用
*/

template<typename T>
struct vec {
	T x, y;
	vec(T x, T y) :x(x), y(y) {}
	vec() :x(0), y(0) {}
	T prod(vec v) const {
		return x * v.x + y * v.y;
	}
	long double abs() const {
		return sqrtl( x * x + y * y);
	}
	vec operator+(const vec v) const {
		return vec(x + v.x, y + v.y);
	}
	T operator*(const vec v) const {
		return prod(v);
	}
	vec& operator+=(const vec v) {
		(*this) = (*this) + v;
		return *this;
	}
	vec& operator*=(const T v) {
		x *= v;
		y *= v;
		return (*this);
	}
	vec rot() const { // +90度回転
		return vec(-y, x);
	}
	double rad() const {
		return atan2<double>(y, x);
	}
	bool operator<(const vec& v) const {
		return rad() < v.rad();
	}
	bool operator==(const vec& v) const {
		return !(x * v.y - y * v.x);
	}
};