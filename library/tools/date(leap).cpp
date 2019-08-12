/*
日付関連の関数まとめ
@verify https://leetcode.com/submissions/detail/251010666/
*/
#include<bits/stdc++.h>
using namespace std;

bool leap(int year){
    if (year % 4==0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            }
        }
        else {
            return true;
        }
    }
    return false;
}

int m[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct date{
    int year,month,day;
};

int nthday(date d){// 1/1からかぞえて何番目の日かを返す(0-index)
    int m[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if(leap(d.year)){
        m[1]++;
    }
    int res = 0;
    for(int i=0;i<d.month-1&&i<12;++i){
        res+=m[i];
    }
    res+=d.day-1;
    return res;
}

date nthday(int year,int n){//year/1/1から数えてn番目の日を返す(n<=365,0-index)
    int m[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if(leap){
        m[1]++;
    }
    date res = {year,1,1};
    for(int i=0;n>=m[i];++i){
        n-=m[i];
        res.month++;
    }
    res.day+=n;
    return res;
}


class date {
public:
	int year, month, day;
	int	m[12]	= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int lm[12]	= { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	date(int y, int m, int d) :year(y), month(m), day(d) {}
	bool leap(int y) {
		if (y % 4 == 0) {
			if (y % 100 == 0) {
				if (y % 400 == 0) {
					return true;
				}
			} else {
				return true;
			}
		}
		return false;
	}

	void nextday() {
		if (leap(this->year)) {
			if (this->day == this->lm[this->month - 1]) {
				if (this->month == 12) {
					this->year++;
					this->month = this->day = 1;
				} else {
					this->month++;
					this->day = 1;
				}
			} else {
				day++;
			}
		} else {
			if (this->day == this->m[this->month - 1]) {
				if (this->month == 12) {
					this->year++;
					this->month = this->day = 1;
				} else {
					this->month++;
					this->day = 1;
				}
			} else {
				day++;
			}
		}
	}
	void prevday() {
		if (day == 1) {
			if (this->month == 3&& leap(this->year)) {
				this->month = 2;
				this->day = 29;
			} else {
				this->month--;
				this->day = m[this->month - 1];
			}
		} else {
			day--;
		}
	}

};

int main(){
    date today = {2019,2,10};
    cout << nthday(today) << endl;
    int n = 40;
    date t = nthday(2019,n);
    cout << t.month << " " << t.day << endl;
    return 0;
}