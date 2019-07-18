//comp;less<T>:min,greater<T>:max
template<typename T,class Comp>
vector<T> slide_min(vector<T>& a,int k){
    int n = a.size();
    vector<T> res(n-k+1);
    deque<int> q;
    Comp comp;
    for(int i=0;i<k-1;++i){
        while (!q.empty()&&comp(a[q.back()],a[i])) {
            q.pop_back();
        }
        q.push_back(i);
    }
    for(int i=0;i<n-k+1;++i){
        while (!q.empty()&&comp(a[q.back()],a[i+k-1])) {
            q.pop_back();
        }
        q.push_back(i+k-1);
        res[i] = a[q.front()];
        if(q.front()==i){
            q.pop_front();
        }
    }
    return res;
}