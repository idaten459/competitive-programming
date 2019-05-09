/*
 pair<ll,ll>のソートする際のcomp関数
 1 1
 2 2
 2 1
 の順になる
*/

bool comp(const pair<ll,ll>& left,const pair<ll,ll>& right){
    if(left.first!=right.first){
        return left.second < right.second;
    }else{
        return left.first > right.first;
    }
}