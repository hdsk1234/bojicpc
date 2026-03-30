#include <iostream>
#include <queue>
using namespace std;

int board[100001];

int main() {
    int N, K;
    int ans = 0;
    queue< pair<int, int> > q;

    cin >> N >> K;
    q.push({N, 0});
    board[N] = 1;

    while(1) {
        int cur_pos = q.front().first;
        int cur_time = q.front().second;

        if(cur_pos == K) {
            cout << cur_time;
            return 0;
        }

        int t = cur_pos;
        while(t != 0 && t*2 <= 100000) {
            if(!board[t*2]) {
                q.push({t*2, cur_time});
                board[t*2] = 1;
            }
            t *= 2;
        } // while
        

        if(cur_pos+1 <= 100000 && !board[cur_pos+1]) {
            q.push({cur_pos+1, cur_time+1});
            board[cur_pos+1] = 1;
        }
        
        if(cur_pos-1 >= 0 && !board[cur_pos-1]) {
            q.push({cur_pos-1, cur_time+1});
            board[cur_pos-1] = 1;
        }
        
        q.pop();
    } // while


    return 0;
}