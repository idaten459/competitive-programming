/*
文字列S,Tに対して、
O(|S|)でSuffix Arrayを構築する
O(|T|log|S|)で検索するができる。
find_beginは先頭|T|文字だけ見たときに、t以上のsuffixとなる最小のindexを返す
find_endは先頭|T|文字だけ見たときに、t以下のsuffixとなる最大のindexを返す
今回の実装だと計算量正確には文字種をWとしてO(|S|+W)なのでW=10^9みたいな場合には不向き、座圧すればいいが計算量が悪化するのでしたくない
*/

int get_front(vector<int>& t, vector<int>& sum, vector<int>& ch, int num) {
    int res = sum[t[num]];
    res += ch[t[num]]++;
    return res;
}

int get_back(vector<int>& t, vector<int>& sum, vector<int>& ct, int num) {
    int res = sum[t[num] + 1] - 1;
    res -= ct[t[num]]++;
    return res;
}

void induced_sort(vector<int>& t, vector<int>& table, vector<int>& sum, vector<int>& ls, int ma) {
    int n = t.size();
    vector<int> ch(ma + 1, 0), ct(ma + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (table[i] >= 0) {
            int ind = table[i] - 1;
            if (ind >= 0 && ls[ind]) {
                int d = get_front(t, sum, ch, ind);
                table[d] = ind;
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        if (table[i] >= 0) {
            int ind = table[i] - 1;
            if (ind >= 0 && !ls[ind]) {
                int d = get_back(t, sum, ct, ind);
                table[d] = ind;
            }
        }
    }
}

bool is_lms(vector<int>& ls, int ind) {
    return ind > 0 && ls[ind - 1] && !ls[ind];
}

template<typename T>
vector<T> substr(vector<T> v, int a, int b) { // v[a,b)
    a = max(0, a);
    b = min(v.size() - 1, b);
    vector<T> res(max(0, b - a));
    for (int i = a; i < b; i++) {
        res[i - a] = v[i];
    }
    return res;
}

vector<int> sais(vector<int>& s) {
    int n = s.size();
    if (n == 1) {
        return vector<int>(1, 0);
    }
    int m = *min_element(s.begin(), s.end());
    if (m != 1) { // 最小値が1となるように変換
        for (int i = 0; i < n; ++i) {
            s[i] -= m - 1;
        }
    }
    int sent = 0; // 番兵が0
    vector<int> t = s;
    t.push_back(sent);
    n++;
    vector<int> ls(n); // 1がl,0がs
    ls.back() = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (t[i] == t[i + 1]) {
            ls[i] = ls[i + 1];
        } else {
            ls[i] = t[i] > t[i + 1];
        }
    }
    vector<int> lms;
    for (int i = 1; i < n; ++i) {
        if (ls[i - 1] && !ls[i]) {
            lms.push_back(i);
        }
    }
    int ma = *max_element(s.begin(), s.end());
    vector<int> cnt(ma + 1, 0);
    for (auto&& v : t) {
        cnt[v]++;
    }
    vector<int> sum(cnt.size() + 1);
    sum[0] = 0;
    for (int i = 0; i < cnt.size(); ++i) {
        sum[i + 1] = sum[i] + cnt[i];
    }
    vector<int> table(n, -1), ch(ma + 1, 0);
    for (int i = (int)lms.size() - 1; i >= 0; --i) {
        int ind = lms[i];
        int d = get_back(t, sum, ch, ind);
        table[d] = lms[i];
    }
    induced_sort(t, table, sum, ls, ma);
    //sorted lms-substring
    vector<int> nt(lms.size());
    int cn = 0;
    vector<int> lms_index(n, -1); // iがlmsのうち先頭から何番目に現れるか
    for (int i = 0; i < n; ++i) {
        if (is_lms(ls, i)) {
            lms_index[i] = cn++;
        }
    }
    cn = 1;
    int sub = 0, preind = -1;
    for (int i = 0; i < n; ++i) { // lms-substringを復元
        int ind = table[i];
        if (is_lms(ls, ind)) {
            if (cn > 1) {
                int a = lms[preind];
                int b = lms[min<int>(preind + 1, lms.size() - 1)];
                int c = lms[lms_index[ind]];
                int d = lms[min<int>(lms_index[ind] + 1, lms.size() - 1)];
                int pre_len = b - a;
                int post_len = d - c;
                if (pre_len != post_len) {
                    sub--;
                } else {
                    for (int j = 0; j < pre_len; j++) {
                        if (t[j + a] != t[j + c]) {
                            sub--;
                            break;
                        }
                    }
                }
                sub++;
            }
            nt[lms_index[ind]] = cn - sub;
            preind = lms_index[ind];
            cn++;
        }
    }
    // ntのSAを求めるs
    auto lms_sa = sais(nt);
    std::fill(ch.begin(), ch.end(), 0);
    std::fill(table.begin(), table.end(), 0);
    for (int i = (int)lms_sa.size() - 1; i >= 0; --i) {
        int ind = lms[lms_sa[i]];
        int d = get_back(t, sum, ch, ind);
        table[d] = ind;
    }
    induced_sort(t, table, sum, ls, ma);
    vector<int> res(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        res[i] = table[i + 1];
    }
    return res;
}

vector<int> stovi(string& s) {
    int n = s.size();
    vector<int> res(n);
    char mi = *min_element(s.begin(), s.end());
    for (int i = 0; i < n; i++) {
        res[i] = s[i] - mi + 1;
    }
    return res;
}

int find_begin_naive(string& s, vector<int>& sa, string& str) {
    int ng = -1, ok = sa.size();
    int l = str.size();
    while (abs(ng - ok) > 1) {
        int mid = (ng + ok) / 2;
        int suffix_ind = sa[mid];
        int r = min<int>(l, s.size() - suffix_ind);
        string suffix = s.substr(suffix_ind, r);
        if (suffix >= str) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int find_end_naive(string& s, vector<int>& sa, string& str) {
    int ok = -1, ng = sa.size();
    int l = str.size();
    while (abs(ng - ok) > 1) {
        int mid = (ng + ok) / 2;
        int suffix_ind = sa[mid];
        int r = min<int>(l, s.size() - suffix_ind);
        string suffix = s.substr(suffix_ind, r);
        if (suffix <= str) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int count(string& s, vector<int>& sa, string& str) {
    int beg = find_begin_naive(s, sa, str);
    int en = find_end_naive(s, sa, str);
    return en - beg + 1;
}


void solve() {
    string t;
    cin >> t;
    auto vi = stovi(t);
    auto sa = sais(vi);
    int q;
    cin >> q;
    REP(loop, q) {
        string p;
        cin >> p;
        int c = count(t, sa, p);
    }
}