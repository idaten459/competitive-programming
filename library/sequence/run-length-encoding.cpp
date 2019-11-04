/*
run-length-enconding
ランレングス圧縮
1 1 2 2 2
を
{
    <2,1>,
    <3,2>
}
という圧縮方法
*/

template <typename T>
vector<pair<int, T>> rle(vector<T> a)
{
    int n = (int)a.size();
    vector<pair<int, T>> res;
    if (n == 0)
    {
        return res;
    }
    T now = a[0];
    int con = 0;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] == now)
        {
            con++;
        }
        else
        {
            res.push_back(pair<int, T>(con, now));
            now = a[i];
            con = 1;
        }
    }
    res.push_back(pair<int, T>(con, now));
    return res;
}
