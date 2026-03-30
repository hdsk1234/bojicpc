#include <iostream>
#include <queue>
using namespace std;

int board[100001];

int main() {
    int N, K;
    int ans1 = 0;
    int ans2 = 0;
    int end_flag = 0;
    cin >> N >> K;

    queue<int> q;
    q.push(N);
    board[N] = 1;

    while(1) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            int cur = q.front();
            board[cur] = 1;

            if(cur == K) {
                ans2++;
                end_flag = 1;
                q.pop();
                continue;
            }

            if(cur-1 == K || cur+1 == K || cur*2 == K) {
                q.pop();
                q.push(K);
                continue;
            }

            if(cur-1 >= 0 && !board[cur-1]) {
                q.push(cur-1);
            }

            if(cur+1 <= 100000 && !board[cur+1]) {
                q.push(cur+1);
            }

            if(cur*2 <= 100000 && !board[cur*2]) {
                q.push(cur*2);
            }

            q.pop();
        } // for i
        if(end_flag) break;
        ans1++;
    } // while

    cout << ans1 << endl;
    cout << ans2;
    return 0;
}