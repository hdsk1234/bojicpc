#include <iostream>
using namespace std;

int N, M, x, y, k;
int board[20][20];


void roll_dice(int command, int& top, int& bottom, int& front, int& back, int& left, int& right) {
    int t;
    switch(command) {
        case 1: // 동
            if(x+1 >= M) return;
            x++;

            t = top;
            top = left;
            left = bottom;
            bottom = right;
            right = t;
            break;
        case 2: // 서
            if(x-1 < 0) return;
            x--;

            t = top;
            top = right;
            right = bottom;
            bottom = left;
            left = t;
            break;
        case 3: // 북
            if(y-1 < 0) return;
            y--;

            t = top;
            top = back;
            back = bottom;
            bottom = front;
            front = t;
            break;
        case 4: // 남
            if(y+1 >= N) return;
            y++;

            t = top;
            top = front;
            front = bottom;
            bottom = back;
            back = t;
            break;
    }

    if(board[y][x] == 0) {
        board[y][x] = bottom;
    }
    else {
        bottom = board[y][x];
        board[y][x] = 0;
    }

    cout << top << '\n';

} // roll_dice()

int main() {
    int top = 0;
    int bottom = 0;
    int front = 0;
    int back = 0;
    int left = 0;
    int right = 0;

    cin >> N >> M >> y >> x >> k;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }

    for(int h = 0; h < k; h++) {
        int command;
        cin >> command;

        roll_dice(command, top, bottom, front, back, left, right);
    } // for h

    return 0;
}