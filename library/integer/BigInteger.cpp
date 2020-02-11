/*
多倍長整数のライブラリ
計算量は桁数をLとして加減算がO(L),乗算がO(L^2)
FFTを用いて乗算をO(L*log L)になるらしいが未実装(そもそもFFT自体がまだ)
*/

class BigInteger {
public:
	using ll = int64_t;
	vector<ll> val; // 10^9ごとに保管
	int neg = 0; // 1のとき負
	const ll u = 1e9;
	BigInteger(vector<ll>& a) :val(a) {}
	BigInteger(int a) {
		val.clear();
		val.push_back(a);
	}
	BigInteger(const string& s) {
		ll tmp = 0;
		int l = (int)s.size();
		int sh = 0;
		if (s[0] == '-') {
			neg = 1;
			sh = 1;
		}
		for (int i = sh; i < l; ++i) {
			tmp *= 10;
			tmp += (ll)s[i] - '0';
			if ((l - 1 - i) % 9 == 0) {
				val.push_back(tmp);
				tmp = 0;
			}
		}
		reverse(val.begin(), val.end());
		supplies();
	}
	BigInteger() {
		val.push_back(0);
	}
	void supplies() {
		int l = val.size();
		for (int i = l - 1; i > 0; --i) {
			if (val[i] == 0) {
				val.pop_back();
			} else {
				break;
			}
		}
	}
	
	ll get(int index) {
		if (size() > index) {
			return val[index];
		} else {
			return 0;
		}
	}
	BigInteger add(BigInteger a) { // this + a
		if (this->neg != a.neg) {
			a.neg = !a.neg;
			return sub(a);
		}
		BigInteger res;
		int m = max(this->size(), a.size());
		res.val.resize(m);
		int carry = 0;
		for (int i = 0; i < m; ++i) {
			res.val[i] = (*this)[i] + a[i] + carry;
			carry = res.val[i] / u; // 此処の演算は2冪の方が速い
			res.val[i] %= u;
		}
		if (carry > 0) {
			res.val.push_back(carry);
		}
		res.neg = this->neg;
		res.neg_zero();
		return res;
	}
	BigInteger sub(BigInteger a) { // this - a
		if (this->neg != a.neg) {
			a.neg = !a.neg;
			return add(a);
		}
		int m = max(this->size(), a.size());
		BigInteger res;
		res.neg = this->neg;
		res.val.resize(m);
		int borrow = 0;
		if (unsinged_greater(a)) {
			for (int i = 0; i < m; ++i) {
				res.val[i] = (*this)[i] - a[i] - borrow;
				borrow = 0;
				if (res.val[i] < 0) {
					borrow = (std::abs(res.val[i]) + u - 1) / u;
					res.val[i] += borrow * u;
				}
			}
		} else {
			res.neg = !res.neg;
			for (int i = 0; i < m; ++i) {
				res.val[i] = a[i] - (*this)[i] - borrow;
				borrow = 0;
				if (res.val[i] < 0) {
					borrow = (std::abs(res.val[i]) + u - 1) / u;
					res.val[i] += borrow * u;
				}
			}
		}
		res.supplies();
		res.neg_zero();
		return res;
	}
	BigInteger mul(BigInteger a) { // this * a
		BigInteger res;
		res.neg = this->neg ^ a.neg;
		int m = this->size() + a.size();
		res.val.resize(m + 2,0);
		vector<ll> tmp(this->size() + 1);
		ll carry = 0;
		for (int j = 0; j < a.size(); ++j) {
			for (int i = 0; i < this->size(); ++i) {
				ll t = (*this)[i] * a[j];
				t += carry;
				res.val[i + j] += t;
				carry = res.val[i + j] / u;
				res.val[i + j] %= u;
				//tmp[i + j];
			}
			res.val[j + this->size()] += carry;
			carry = 0;
		}
		res.val[a.size() + this->size()] += carry;
		res.supplies();
		res.neg_zero();
		return res;
	}
	int size() {
		this->supplies();
		return this->val.size();
	}
	bool unsinged_greater(BigInteger a) { // 符号を無視したときのa>b
		if (this->size() > a.size()) {
			return true;
		}
		if (this->size() < a.size()) {
			return false;
		}
		int s = this->size();
		for (int i = s - 1; i >= 0; --i) {
			if ((*this)[i] > a[i]) {
				return true;
			} else if ((*this)[i] < a[i]) {
				return false;
			}
		}
		return false;
	}
	bool is_zero() {
		if (this->size() == 1 && val[0] == 0) {
			return true;
		}
		return false;
	}
	void neg_zero() {
		if (this->is_zero() && this->neg) {
			this->neg = 0;
		}
	}
	bool signed_equal(BigInteger a) {
		if (this->neg != a.neg) {
			return false;
		}
		if (this->val.size() != a.size()) {
			return false;
		}
		for (int i = 0; i < this->val.size(); ++i) {
			if (this->val[i] != a.val[i]) {
				return false;
			}
		}
		return true;
	}
	bool signed_greater(BigInteger a) { // 符号を考慮したときのa>b
		this->neg_zero();
		a.neg_zero();
		if (this->neg) {
			if (a.neg) {
				return (!unsinged_greater(a)) || signed_equal(a);
			} else {
				return false;
			}
		} else {
			if (a.neg) {
				return true;
			} else {
				return unsinged_greater(a);
			}
		}
		return false;
	}
	string to_string() { // 此処の処理は10冪の方が圧倒的に楽
		string res = "";
		stringstream ss;
		this->neg_zero();
		if (this->neg) {
			ss << '-';
		}
		int l = val.size();
		for (int i = l - 1; i >= 0; --i) {
			if (i == l - 1) {
				ss << val[i];
			} else {
				ss << std::setw(9) << std::setfill('0') << val[i];
			}
		}
		return ss.str();
	}
	ll operator[](int a) { return get(a); }
	BigInteger operator+(BigInteger a) { return this->add(a); }
	BigInteger operator-(BigInteger a) { return this->sub(a); }
	BigInteger operator*(BigInteger a) { return this->mul(a); }
	void operator+=(BigInteger a) {
		BigInteger res = this->add(a);
		this->neg = res.neg;
		this->val = res.val;
	}
	void operator-=(BigInteger a) {
		BigInteger res = this->sub(a);
		this->neg = res.neg;
		this->val = res.val;
	}
	void operator*=(BigInteger a) {
		BigInteger res = this->mul(a);
		this->neg = res.neg;
		this->val = res.val;
	}
};

template<typename T> void put(T a) {
	cout << a << endl;
}

string solve(string a, string b) {
	BigInteger b1(a), b2(b);
	b1 -= b2;
	return b1.to_string();
}

int main() {
	string a, b;
	cin >> a >> b;
	BigInteger b1(a), b2(b);
	b1 *= b2;
	cout << b1.to_string() << endl;
	
	return 0;
}