template<typename T>
vector<T> lis_vec(vector<T> a, bool broad = true) {//broad=true:広義、false:狭義
	int n = a.size();
	vector<T> lis;
	lis.push_back(a[0]);
	for (int i = 1; i < a.size(); ++i) {
		if (broad) {
			if (lis.back() <= a[i]) {
				lis.push_back(a[i]);
			}
			else {
				auto itr = upper_bound(all(lis), a[i]) - lis.begin();
				lis[itr] = a[i];
			}
		}
		else {
			if (lis.back() < a[i]) {
				lis.push_back(a[i]);
			}
			else {
				auto itr = lower_bound(all(lis), a[i]) - lis.begin();
				lis[itr] = a[i];
			}
		}

	}
	return lis;
}
