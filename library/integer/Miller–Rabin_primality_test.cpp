/*
ミラービン素数判定法
計算量はO(klog(n)^3)
vrify @https://yukicoder.me/problems/no/3030
    https://yukicoder.me/submissions/349610
caution
こどふぉではu128が使えないので、Miller–Rabin_test_CF_edition.cppを使うこと！
*/
using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;

template <class Uint, class BinOp>
bool is_prime_impl(const Uint &n, const Uint *witness, BinOp modmul) {
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    const Uint m = n - 1, d = m / (m & -m);
    auto modpow = [&](Uint a, Uint b) {
        Uint res = 1;
        for (; b; b /= 2) {
            if (b & 1) res = modmul(res, a);
            a = modmul(a, a);
        }
        return res;
    };
    auto suspect = [&](Uint a, Uint t) {
        a = modpow(a, t);
        while (t != n - 1 && a != 1 && a != n - 1) {
            a = modmul(a, a);
            t = modmul(t, 2);
        }
        return a == n - 1 || t % 2 == 1;
    };
    for (const Uint *w = witness; *w; w++) {
        if (*w % n != 0 && !suspect(*w, d)) return false;
    }
    return true;
}

bool is_prime(const u128 &n) {
    assert(n < 1ULL << 63);
    if (n < 1ULL << 32) {
        // n < 2^32
        constexpr u64 witness[] = {2, 7, 61, 0};
        auto modmul = [&](u64 a, u64 b) { return a * b % n; };
        return is_prime_impl<u64>(n, witness, modmul);
    } else {
        // n < 2^63
        constexpr u128 witness[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};
        // if u128 is available
        auto modmul = [&](u128 a, u128 b) { return a * b % n; };
        // otherwise
        // auto modmul = [&](u64 a, u64 b) {
        //     u64 res = 0;
        //     for (; b; b /= 2) {
        //         if (b & 1) res = (res + a) % n;
        //         a = (a + a) % n;
        //     }
        //     return res;
        // };
        return is_prime_impl<u128>(n, witness, modmul);
    }
}
