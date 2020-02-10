#include <bits/stdc++.h>
using namespace std;

class BigInteger {
public:
	using ll = int64_t;
	vector<int> val; // 10^9ごとに保管
	int sign = 0; // 1のとき負
	const ll u = 1e9;
	BigInteger(vector<int>& a) :val(a) {}
	BigInteger(int a) {
		val.clear();
		val.push_back(a);
	}
	/*BigInteger(const string&& s) {
	}*/
	BigInteger(const string& s) {
		ll tmp = 0;
		int l = (int)s.size();
		int sh = 0;
		if (s[0] == '-') {
			sign = 1;
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
	BigInteger() {}
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
	BigInteger inv() {
		this->sign = !this->sign;
		return *this;
	}
	ll get(int index) {
		if (val.size() < index) {
			return val[index];
		} else {
			return 0;
		}
	}
	BigInteger add(BigInteger a) { // this + a
		if (this->sign != a.sign) {
			a.sign = !a.sign;
			return sub(a.inv());
		}
		this->supplies();
		a.supplies();
		BigInteger res;
		int m = max(this->val.size(), a.val.size());
		res.val.resize(m);
		int carry = 0;
		for (int i = 0; i < m; ++i) {
			res.val[i] = this->val[i] + a.val[i] + carry;
			carry = res.val[i] / u; // 此処の演算は2冪の方が速い
		}
		if (carry > 0) {
			res.val.push_back(carry);
		}
		res.sign = this->sign;
		return res;
	}
	BigInteger sub(BigInteger a) { // this - a
		if (this->sign == a.sign) {
			a.sign = !a.sign;
			return sub(a.inv());
		}
		this->supplies();
		a.supplies();
		int m = max(this->val.size(), a.val.size());
		BigInteger res;
		res.sign = this -> sign;
		res.val.resize(m);
		for (int i = m-1; i>= 0; --i) {
			
		}
		res.supplies();
		return res;
	}
	int size() {
		this->supplies();
		return this->val.size();
	}
	bool unsinged_greater(BigInteger a) { // 符号を無視したときのa>b
		//this->supplies();
		//a.supplies();
		if (this->size() > a.size()) {
			return true;
		}
		if (this->size() < a.size()) {
			return false;
		}
		int s = size();
		for (int i = s - 1; i >= 0; --i) {
			if (val[i] > a.val[i]) {
				return true;
			} else if (val[i] < a.val[i]) {
				return false;
			}
		}
		return false;
	}
	bool signed_greater(BigInteger a) { // 符号を考慮したときのa>b
		if (this->sign) {
			if (a.sign) {

			} else {
				return false; // -0の時やばいいい
			}
		} else {
			if (a.sign) {
				return true;
			} else {

			}
		}
	}
	string to_string() { // 此処の処理は10冪の方が圧倒的に楽
		string res = "";
		stringstream ss;
		//bool first_zero = true;
		int first_zero = 0;
		for (int i = 0; i < val.size(); ++i) {
			if (first_zero==0) {
				if (val[i] != 0) {
					first_zero = 1;
					ss << val[i];
				}
			} else {
				ss << std::setw(9) << std::setfill('0') << val[i];
			}
		}
		if (first_zero == 0) {
			ss << '0';
		}
		
		return ss.str();
	}
	ll operator[](int a) { return get(a); }
};

template<typename T> void put(T a) {
	cout << a << endl;
}

int main() {
	string s = "123456789012345657890";
	BigInteger b1(s);
	//b1 = b1.add("123");
	cout << b1.to_string() << endl;
	return 0;
}