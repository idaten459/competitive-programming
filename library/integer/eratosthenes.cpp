template <class T>
vector<T> eratosthenes(T n){
    vector<T> res;
    vector<bool> sieve(n + 1, true);
    sieve[0] = false;
    sieve[1] = false;
    for (T i = 2; i * i < n + 1; ++i){
        if (sieve[i]){
            for (T j = i * i; j < n + 1; j += i){
                sieve[j] = false;
            }
        }
    }
    for (T i = 0; i < n + 1; ++i){
        if (sieve[i]){
            res.push_back(i);
        }
    }
    return res;
}
