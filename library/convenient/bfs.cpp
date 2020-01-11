/*
簡単だが、長いのでライブラリ化
bfsライブラリ
.##
..#
#..
##.
みたいなやつ
(sy,sx) = (0,0)としたが適宜変更して
*/
int dx[4] = {1,0,-1, 0};
int dy[4] = {0,1, 0,-1};

int main(){
    int h,w;
    cin >> h >> w;
    int sy=0,sx=0;
    vector<vector<char>> a(h,vector<char>(w,0));
    REP(i,h){
        REP(j,w){
            cin >> a[i][j];
        }
    }
    vector<vector<int>> d(h,vector<int>(w,INT_MAX));
    queue<P> q;
    q.push(P(sy,sx));
    
    while(q.size()>0){
        
        P p = q.front();
        q.pop();
        
        REP(i,4){
            int ny = p.first +dy[i];
            int nx = p.second+dx[i];
            if(0<=nx&&nx<w&&0<=ny&&ny<h&&a[ny][nx]=='.'&&d[ny][nx]==INT_MAX){
                q.push(P(ny,nx));
                d[ny][nx]=d[p.first][p.second]+1;
            }
        }
        
    }
    int res = 0;
    REP(i,h){
        REP(j,w){
            chmax(res,d[i][j]);
        }
    }
    put(res);
    return 0;
}
