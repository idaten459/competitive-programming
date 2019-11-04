/*
string to vector<char>
vector<T>関連のライブラリを適用するために、stringをvector<char>に変換する
計算量はO(n);
*/

vector<char> stv(string s){
    int n = (int)s.size();
    vector<char> res(n);
    for(int i=0;i<n;++i){
        res[i] = s[i];
    }
    return res;
}