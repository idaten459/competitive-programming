/*
拡張ユークリッドの互除法
ax+by=cの解を生成 (a,b,c>0) 解が存在しないときは(0,0)を返す
計算量はO(log(a))
@verify https://atcoder.jp/contests/agc025/submissions/8779565
*/

pair<ll, ll> ee(ll a, ll b) {// ax+by=gcd(a,b)の解を生成する(a,b>0)
	pair<ll, ll> res = pair<ll, ll>(0,1);
	vector<ll> temp;
	ll c;
	while (b) {
		temp.push_back(a / b); 
		c = a % b;
		a = b;
		b = c;
	}
	int l = temp.size();
	for (int i = l - 2; i >= 0 ; --i) {
		res = pair<ll, ll>(res.second, res.first - temp[i] * res.second);
	}
	return res;
}

pair<ll, ll> extended_euclidean(ll a, ll b, ll c) {//ax+by=cの解を生成 (a,b,c>0) (0,0)は解が存在しない
	ll g = gcd(a, b);
	if (c % g != 0) {
		return pair<ll, ll>(0, 0);
	}
	pair<ll, ll> res = ee(a, b);
	res.first *= c / g;
	res.second *= c / g;
	return res;
}