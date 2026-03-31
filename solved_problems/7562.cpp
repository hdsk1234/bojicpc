#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int visited[300][300];
int dir[8][2] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };

void solve(int l, int y1, int x1, int y2, int x2) {
    int ans = 0;
    queue< pair<int, int> > q;
    q.push({y1, x1});
    visited[y1][x1] = 1;

    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            int cur_y = q.front().first;
            int cur_x = q.front().second;

            if(cur_y == y2 && cur_x == x2) {
                cout << ans << '\n';
                return;
            }

            for(int j = 0; j < 8; j++) {
                int nxt_y = cur_y + dir[j][0];
                int nxt_x = cur_x + dir[j][1];

                if(nxt_y < 0 || nxt_y >= l || nxt_x < 0 || nxt_x >= l) continue;
                if(visited[nxt_y][nxt_x]) continue;

                q.push({nxt_y, nxt_x});
                visited[nxt_y][nxt_x] = 1;
            } // for j
            q.pop();
        } // for i
        ans++;
    } // while
    return;
}

int main() {
    int TESTCASE;
    cin >> TESTCASE;

    for(int testcase = 0; testcase < TESTCASE; testcase++) {
        memset(visited, 0, sizeof(visited));
        int l;
        int y1, x1, y2, x2;
        cin >> l;
        cin >> y1 >> x1 >> y2 >> x2;

        solve(l, y1, x1, y2, x2);
    } // for testcase
    return 0;
}