/*
res[i] := iの最小素因数(smallest prime factor)を返す
計算量はO(n logn)
*/

template<typename T>
vector<T> smallest_prime_factors(T n) {
    vector<T> res(n + 1, -1);
    for (T i = 2; i <= n; ++i) {
        if (res[i] == -1) {
            res[i] = i;
            int64_t start = (int64_t)i * i;
            for (int64_t j = start; j <= n; j += i) {
                res[j] = i;
            }
        }
    }
    return res;
}