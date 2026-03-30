#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int M, N, K;
int board[101][101];
int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
vector<int> ans;

void bfs(int x, int y) {
    queue< pair<int, int> > q;
    q.push({x, y});
    board[x][y] = 1;
    int result = 0;

    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        for(int i = 0; i < 4; i++) {
            int nxtX = curX + dir[i][0];
            int nxtY = curY + dir[i][1];

            if(nxtY < 0 || nxtY >= M || nxtX < 0 || nxtX >= N) continue;
            if(board[nxtX][nxtY]) continue;

            q.push({nxtX, nxtY});
            board[nxtX][nxtY] = 1;
        } // for i
        q.pop();
        result++;
    } // while

    ans.push_back(result);
}

int main() {
    cin >> M >> N >> K;

    for(int i = 0; i < K; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        for(int j = x1; j < x2; j++) {
            for(int k = y1; k < y2; k++) {
                board[j][k] = 1;
            }
        }
    } // for i

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(!board[i][j]) bfs(i, j);
        }
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++) cout << ans[i] << " ";

    return 0;
}