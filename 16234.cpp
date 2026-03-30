#include <iostream>
#include <queue>
using namespace std;

int N, L, R;
int A[50][50];


bool bfs() { // 인구이동을 수행하고 수행여부를 리턴
    bool rtn = false;
    int visited[50][50] = { 0 };
 

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            queue< pair <int, int> > q;
            vector< pair <int, int> > v;
            if(visited[i][j]) continue;
            
            q.push(make_pair(i, j));
            v.push_back(make_pair(i, j));
            visited[i][j] = 1;
            int sum = A[i][j];
            int pop = 1;

            while(!q.empty()) {
                int cur_y = q.front().first;
                int cur_x = q.front().second;

                int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
                for(int k = 0; k < 4; k++) {
                    int nxt_y = cur_y + dir[k][0];
                    int nxt_x = cur_x + dir[k][1];
                    int pop_gap = abs(A[cur_y][cur_x] - A[nxt_y][nxt_x]);

                    if(visited[nxt_y][nxt_x]) continue;
                    if(nxt_y < 0 || nxt_y >= N || nxt_x < 0 || nxt_x >= N) continue;
                    if(L > pop_gap || R < pop_gap) continue;

                    rtn = true;
                    q.push(make_pair(nxt_y, nxt_x));
                    v.push_back(make_pair(nxt_y, nxt_x));  
                    visited[nxt_y][nxt_x] = 1;
                    sum += A[nxt_y][nxt_x]; 
                    pop++;
                } // for k
                q.pop();
            } // while

            int avg = sum / pop;
            for(int k = 0; k < v.size(); k++) {
                int cur_y = v[k].first;
                int cur_x = v[k].second;

                A[cur_y][cur_x] = avg;
            }
            
        } // for j
    } // for i

    return rtn;

} // bfs()


int main () {
    int ans = 0;

    cin >> N >> L >> R;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }


    while(bfs()) {
        ans++;
    }

    cout << ans;

    return 0;
}