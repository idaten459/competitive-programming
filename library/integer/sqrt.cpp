/*
n>=0が前提
flag=true, √n以下の最大の整数
flag=false,√n以上の最小の整数
*/

template<typename T>
T sqrtInt(T n, bool flag = true) {
	T ok = 0, ng = 0;
	if (flag) {
		ng = n;
		while (abs<T>(ng - ok) > 1) {
			T mid = (ng + ok) / 2;
			if (mid * mid > n) {
				ng = mid;
			} else {
				ok = mid;
			}
		}
	} else {
		ok = n;
		while (abs<T>(ok - ng) > 1) {
			T mid = (ng + ok) / 2;
			if (mid * mid < n) {
				ng = mid;
			} else {
				ok = mid;
			}
		}
	}
	return ok;
}
