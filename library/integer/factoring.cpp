/*
素因数分解をするライブラリ
計算量はO(√n)
vector<piar>の形式で返し、firstが素数、secondeが指数
n=1の時に注意

計算量は
n<=2^20のとき、O(n log(n))
n>2^20のとき、O(sqrt(n))くらい
新式
@verify https://codeforces.com/contest/1047/submission/77143220
*/

// 旧式
template<class T> inline vector<pair<T,int>> factoring(T n){
    using p = pair<T,int>;
    using vp = vector<p>;
    vp res;
    T k = n;
    if(n%2==0){
        res.push_back(p(2,1));
        n/=2;
        while (n%2==0) {
            res[0].second++;
            n/=2;
        }
    }
    for(T i=3;i<=n&&i*i<=k;i+=2){
        if(n%i==0){
            res.push_back(p(i,1));
            n/=i;
            while (n%i==0) {
                res.back().second++;
                n/=i;
            }
        }
    }
    if(n!=1){
        res.push_back(p(n,1));
    }
    return res;
}

// 新式
template<typename T> inline vector<pair<T, int>> factoring(T n) {
	static int64_t border = 1 << 20;
	static vector<int> smallest_prime_factors(4, 0);
	smallest_prime_factors[2] = 2;
	smallest_prime_factors[3] = 3;
	vector<pair<T, int>> res;
	if (n <= border) {
		int64_t preSize = smallest_prime_factors.size();
		if (preSize <= n) {
			int64_t t = preSize;
			while (t <= n) {
				t *= 2;
			}
			smallest_prime_factors.resize(t, -1);
			for (int64_t i = 2; i < t; ++i) {
				if (smallest_prime_factors[i] == i) {
					int64_t start = min(i * i, (preSize + i - 1) / i * i);
					for (int64_t j = start; j < t; j += i) {
						if (smallest_prime_factors[j] == -1) {
							smallest_prime_factors[j] = i;
						}
					}
				} else if (smallest_prime_factors[i] == -1) {
					smallest_prime_factors[i] = i;
					int64_t start = i * i;
					for (int64_t j = start; j < t; j += i) {
						if (smallest_prime_factors[j] == -1) {
							smallest_prime_factors[j] = i;
						}
					}
				}
			}
		}
		while (n >= 2) {
			T spf = smallest_prime_factors[n];
			n = n / spf;
			if (res.size()>0 && res.back().first == spf) {
				res.back().second++;
			} else {
				res.push_back(pair<T, int>(spf, 1));
			}
		}
	} else {
		int64_t spfSize = smallest_prime_factors.size();
		vector<pair<T, int>> res2;
		for (int64_t i = 2; i < spfSize && i*i<= n; i++) {
			if (smallest_prime_factors[i] == i) {
				if (n % i == 0) {
					res.push_back(pair<T, int>(i, 1));
					n /= i;
					while (n % i == 0) {
						res.back().second++;
						n /= i;
					}
					if (n <= border) {
						res2 = factoring(n);
						n = 1;
					}
				}
			}
		}
		for (int64_t i = spfSize + 1; i * i <= n; i+= 2) {
			if (n % i == 0) {
				res.push_back(pair<T, int>(i, 1));
				n /= i;
				while (n % i == 0) {
					res.back().second++;
					n /= i;
				}
				if (n <= border) {
					res2 = factoring(n);
					n = 1;
				}
			}
				
		}
		for (auto&& v : res2) {
			res.push_back(v);
		}
		if (n != 1) {
			res.push_back(pair<T, int>(n, 1));
		}
	}
	return res;
}