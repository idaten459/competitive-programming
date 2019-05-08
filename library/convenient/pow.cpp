/* 
pow関数
計算量はO(logY)
単位元は1
*/
template<typename T,typename U>
inline T pow(T x,U exp){
    if(exp<=0){
        return 1;
    }
    if(exp%2==0){
        T d = pow(x,exp/2);
        return d*d;
    }
    else{
        return (x*pow(x,exp-1));
    }
}