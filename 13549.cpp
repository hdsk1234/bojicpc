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

        int t = cur_pos;
        while(t*2 <= 100000) {

            if(t*2 == K) {
                cout << cur_time;
                return 0;
            }
            
            if(!board[t*2]) {
                q.push({t*2, cur_time});
                board[t*2] = 1;
            }
            t *= 2;
        } // while
        
        if(cur_pos+1 == K || cur_pos-1 == K) {
            cout << cur_time+1;
            return 0;
        }

        if(!board[cur_pos+1]) {
            q.push({cur_pos+1, cur_time+1});
            board[cur_pos+1] = 1;
        }
        
        if(!board[cur_pos-1]) {
            q.push({cur_pos-1, cur_time+1});
            board[cur_pos-1] = 1;
        }
        
        ans = cur_time + 1;
        q.pop();
    } // while


    return 0;
}