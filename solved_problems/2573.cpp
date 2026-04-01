#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct State {
    int y;
    int x;
    int value;
};

int N, M;
int board[300][300];
int visited[300][300];
vector< State > has_ice;
int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
int ans;


void updateBoard() { // board를 다음 해의 상태로 바꾼다.

    // 1. next_ice에 안 녹은 얼음만 저장. 다 녹은 얼음은 melt에 따로 저장.
    vector<State> next_ice;
    vector<State> melt;

    for(int i = 0; i < has_ice.size(); i++) {
        int cur_y = has_ice[i].y;
        int cur_x = has_ice[i].x;

        for(int j = 0; j < 4; j++) {
            int nxt_y = cur_y + dir[j][0];
            int nxt_x = cur_x + dir[j][1];

            if(nxt_y < 0 || nxt_y >= N || nxt_x < 0 || nxt_x >= M) continue;
            if(board[nxt_y][nxt_x]) continue;

            has_ice[i].value--;
        } // for j
        if(has_ice[i].value > 0) next_ice.push_back(has_ice[i]); 
        else melt.push_back(has_ice[i]);
    } // for i
    
    // 2. has_ice에 next_ice를 옮겨담고 board 업데이트
    has_ice = next_ice;
    int size = has_ice.size();
    for(int i = 0; i < size; i++) {
        int cur_y = has_ice[i].y;
        int cur_x = has_ice[i].x;

        board[cur_y][cur_x] = has_ice[i].value;
    } // for i

    for(int i = 0; i < melt.size(); i++) {
        int cur_y = melt[i].y;
        int cur_x = melt[i].x;
        board[cur_y][cur_x] = 0;
    }

} // updateBoard()


int iceberg_size(int y, int x) { // 인수로 넘어온 점을 포함한 빙산의 크기를 반환.
    queue< pair<int, int> > q;
    memset(visited, 0, sizeof(visited));
    q.push({y, x});
    visited[y][x] = 1;
    int result = 0;

    while(!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;

        for(int i = 0; i < 4; i++) {
            int nxt_y = cur_y + dir[i][0];
            int nxt_x = cur_x + dir[i][1];

            if(nxt_y < 0 || nxt_y >= N || nxt_x < 0 || nxt_x >= M) continue;
            if(visited[nxt_y][nxt_x]) continue;
            if(!board[nxt_y][nxt_x]) continue;

            q.push({nxt_y, nxt_x});
            visited[nxt_y][nxt_x] = 1;
        } // for i
        q.pop();
        result++;
    } // while()
    return result;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            int t; cin >> t;
            if(t) {
                board[i][j] = t;
                has_ice.push_back({i, j, t});
            }
        }
    }

    while(1) {
        if(has_ice.size() == 0) {
            cout << 0;
            return 0;
        }

        if(iceberg_size(has_ice[0].y, has_ice[0].x) < has_ice.size()) {
            cout << ans;
            break;
        }
        
        updateBoard();
        ans++;
    } // while

    return 0;
}