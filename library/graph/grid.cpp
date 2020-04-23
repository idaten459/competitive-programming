/*
grid graphを扱うのが面倒なのでテンプレート化した。
*/

template<typename T>
	class Grid {
	private:
		int dy[8] = { 1,-1,0,0,1,1,-1,-1 };
		int dx[8] = { 0,0,1,-1,1,-1,1,-1 };
	public:
		vector<vector<T>> g;
		int h;
		int w;
		Grid(int h, int w):h(h),w(w) {
			init(h, w);
		}
		void init(int h, int w) {
			g.resize(h);
			for (int i = 0; i < h; ++i) {
				g[i].resize(w);
			}
		}
		void input() {
			for (int i = 0; i < h; ++i) {
				for (int j = 0; j < w; ++j) {
					cin >> g[i][j];
				}
			}
		}
		bool incl(int y, int x) {
			return 0 <= y && y < h && 0 <= x && x < w;
		}
		int to_num(int y, int x) {
			return y * w + x;
		}
		pair<int, int> to_cor(int num) {
			return pair<int, int>(num / w, num % w);
		}
		vector<vector<int>> to_graph(T disable, int arround=4) {
			vector<vector<int>> path(h * w);
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					if (g[i][j] != disable) {
						for (int k = 0; k < arround; k++) {
							int ny = i + dy[k];
							int nx = j + dx[k];
							if (incl(ny, nx)) {
								int now = to_num(i, j);
								int next = to_num(ny, nx);
								path[now].push_back(next);
							}
						}
					}
				}
			}
			return path;
		}
	};