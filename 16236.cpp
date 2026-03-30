#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int board[20][20];
int N;

struct Fish {
    int y;
    int x;
    int size;
    int dist;
};

bool compare(Fish a, Fish b) {
    if(a.dist != b.dist) {
        return a.dist < b.dist;
    }
    if(a.y != b.y) {
        return a.y < b.y;
    }
    return a.x < b.x;
} // compare()

Fish bfs(int shark_size, int shark_y, int shark_x) { // 먹을 수 있는 가장 가까운 물고기 반환
    int visited[20][20] = {0};
    int dist[20][20] = {0};
    vector<Fish> fishes;
    Fish no_fish = {-1, -1, -1, -1}; // 존재하지 않는 물고기
    fishes.push_back(no_fish);
    queue< pair<int, int> > q;
    int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };

    q.push(make_pair(shark_y, shark_x));
    visited[shark_y][shark_x] = 1;

    while(!q.empty()) {
        auto[cur_y, cur_x] = q.front();

        for(int i = 0; i < 4; i++) {
            int nxt_y = cur_y + dir[i][0];
            int nxt_x = cur_x + dir[i][1];
            int nxt_size = board[nxt_y][nxt_x];

            if(visited[nxt_y][nxt_x] || nxt_y < 0 || nxt_y >= N || nxt_x < 0 || nxt_x >= N) continue;
            
            dist[nxt_y][nxt_x] = dist[cur_y][cur_x] + 1;

            if(nxt_size == 0) { // 빈칸이면 큐에 추가
                q.push(make_pair(nxt_y, nxt_x));
                visited[nxt_y][nxt_x] = 1;
            }
            else if(nxt_size < shark_size) { // 먹을 수 있는 물고기라면
                fishes.push_back({nxt_y, nxt_x, nxt_size, dist[nxt_y][nxt_x]});
            }
            else if(nxt_size == shark_size) { // 같은 크기 물고기라면 큐에 추가
                q.push(make_pair(nxt_y, nxt_x));
                visited[nxt_y][nxt_x] = 1;
            }
            else if(nxt_size > shark_size) { // 큰 물고기면 못 감
                // do nothing
            }
        } // for i

        q.pop();
    } // while

    sort(fishes.begin(), fishes.end(), compare);
    if(fishes.size() == 1) return fishes[0]; // no_fish
    else return fishes[1];
}

int main() {
    int shark_size = 2;
    int shark_eat = 0;
    int shark_y, shark_x;
    int ans = 0;

    cin >> N;
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int t;
            cin >> t;
            board[i][j] = t;
            if(t == 9) {
                shark_y = i;
                shark_x = j;
            }
        } // for j
    } // for i

    while(1) {
        Fish shortest_fish = bfs(shark_size, shark_y, shark_x);
        if(shortest_fish.y == -1) { // 먹을 수 있는 물고기가 없다면 종료한다.
            break;
        }
        else { // 먹을 수 있는 물고기가 하나라도 있다면 제일 가까운 걸 먹는다.
            board[shark_y][shark_x] = 0;
            board[shortest_fish.y][shortest_fish.x] = 9;
            shark_eat++;
            if(shark_eat == shark_size) {
                shark_size++;
                shark_eat = 0;
            }
            shark_y = shortest_fish.y;
            shark_x = shortest_fish.x;
            ans += shortest_fish.dist;
        }
    } // while

    cout << ans;
    return 0;
}