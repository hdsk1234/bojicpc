#include <iostream>
#include <queue>
using namespace std;

struct State { 
    int Ry;
    int Rx;
    int By;
    int Bx;
    int prev_command;
    int move_num;
};

int N, M;
char board[10][10];
pair <int, int> R;
pair <int, int> B;
queue<State> q;
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // 상, 하, 좌, 우

State tilt_Red(int _dir, State& st) {

    int cur_Ry = st.Ry;
    int cur_Rx = st.Rx;
    int cur_By = st.By;
    int cur_Bx = st.Bx;

    int nxt_Ry;
    int nxt_Rx;

    while(1) {
        nxt_Ry = cur_Ry + dir[_dir][0];
        nxt_Rx = cur_Rx + dir[_dir][1];

        if(nxt_Ry < 0 || nxt_Ry >= N || nxt_Rx < 0 || nxt_Rx >= M) {
            st = {cur_Ry, cur_Rx, cur_By, cur_Bx, _dir, st.move_num+1};
            break;
        }
        else if(board[nxt_Ry][nxt_Rx] == '#') {
            st = {cur_Ry, cur_Rx, cur_By, cur_Bx, _dir, st.move_num+1};
            break;
        }
        else if(nxt_Ry == cur_By && nxt_Rx == cur_Bx) {
            st = {cur_Ry, cur_Rx, cur_By, cur_Bx, _dir, st.move_num+1};
            break;
        }
        else if(board[nxt_Ry][nxt_Rx] == '0') {
            st = {nxt_Ry, nxt_Rx, cur_By, cur_Bx, _dir, st.move_num+1};
            break;
        }

        cur_Ry = nxt_Ry;
        cur_Rx = nxt_Rx;
    } // while

    return st;
} // tilt_Red()

State tilt_Blue(int _dir, State& st) {
    int cur_Ry = st.Ry;
    int cur_Rx = st.Rx;
    int cur_By = st.By;
    int cur_Bx = st.Bx;

    int nxt_By;
    int nxt_Bx;

    while(1) {
        nxt_By = cur_By + dir[_dir][0];
        nxt_Bx = cur_Bx + dir[_dir][1];

        if(nxt_By < 0 || nxt_By >= N || nxt_Bx < 0 || nxt_Bx >= M) {
            st = {cur_Ry, cur_Rx, cur_By, cur_Bx, _dir, st.move_num+1};
            break;
        }
        else if(board[nxt_By][nxt_Bx] == '#') {
            st = {cur_Ry, cur_Rx, cur_By, cur_Bx, _dir, st.move_num+1};
            break;
        }
        else if(nxt_By == cur_Ry && nxt_Bx == cur_Rx) {
            st = {cur_Ry, cur_Rx, cur_By, cur_Bx, _dir, st.move_num+1};
            break;
        }
        else if(board[nxt_By][nxt_Bx] == '0') {
            st = {cur_Ry, cur_Rx, nxt_By, nxt_Bx, _dir, st.move_num+1};
            break;
        }
        
        cur_By = nxt_By;
        cur_Bx = nxt_Bx;
    } // while

    return st;
} // tilt_Blue()

State tilt(int dir, State st) {
    int Ry = st.Ry;
    int Rx = st.Rx;
    int By = st.By;
    int Bx = st.Bx;
    int move_num = st.move_num;

    switch(dir) {
        case 0: // 상
            if(Ry > By) { // B부터
                st = tilt_Blue(0, st);
                st = tilt_Red(0, st);
            }
            else { // R부터
                st = tilt_Red(0, st);
                st = tilt_Blue(0, st);
            }
            break;
        case 1: // 하
            if(Ry < By) { // B부터
                st = tilt_Blue(1, st);
                st = tilt_Red(1, st);
            }
            else { // R부터
                st = tilt_Red(1, st);
                st = tilt_Blue(1, st);
            }
            break;
        case 2: // 좌
            if(Rx > Bx) { // B부터
                st = tilt_Blue(2, st);
                st = tilt_Red(2, st);
            }
            else { // R부터
                st = tilt_Red(2, st);
                st = tilt_Blue(2, st);
            }
            break;
        case 3: // 우
            if(Rx < Bx) { // B부터
                st = tilt_Blue(3, st);
                st = tilt_Red(3, st);
            }
            else { // R부터
                st = tilt_Red(3, st);
                st = tilt_Blue(3, st);
            }
            break;
    }

    return st;

} // tilt()

int bfs(State st) {
    q.push(st);
    while(!q.empty()) {
        State cur_st = q.front();

        for(int i = 0; i <= 3; i++) {
            if(cur_st.prev_command == i) continue;
            State nxt_st = tilt(i, cur_st);
            int Ry = nxt_st.Ry;
            int Rx = nxt_st.Rx;
            int By = nxt_st.By;
            int Bx = nxt_st.Bx;

            if(nxt_st.move_num > 10) return -1;
            if(board[By][Bx] == '0') continue;
            if(board[Ry][Rx] == '0') return nxt_st.move_num;

            q.push(nxt_st);
            cout << nxt_st.Ry << " " << nxt_st.Rx << " " << nxt_st.By << " " << nxt_st.Bx << " " << endl;
        }
        q.pop();
    } // while

    return -1;
} // bfs()


int main() {
    cin >> N >> M;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];
            if(board[i][j] == 'R') {
                R = make_pair(i, j);
                board[i][j] = '.';
            }
            else if(board[i][j] == 'B') {
                B = make_pair(i, j);
                board[i][j] = '.';
            }
        }
    }


    State st = {R.first, R.second, B.first, B.second, -1, 0};
    cout << bfs(st);

    return 0;
}