// tilt 함수를 방향마다 한개씩 총 4개를 만든다.
// tilt는 기울이는 방향에 더 치우쳐진 녀석부터 굴린다.
// bfs로 10번까지만 해본다.

#include <iostream>
#include <queue>
using namespace std;

char board[10][10];
// int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
pair<int, int> R_pos;
pair<int, int> B_pos;

struct pos {
    pair<int, int> R;
    pair<int, int> B; 
    
    friend ostream& operator<<(ostream& os, const pos& p) {
        os << p.R.first << " " << p.R.second << " " << p.B.first << " " << p.B.second;
        return os;
    }
};

int tilt(pos cur_pos, pos& nxt_pos, int dir) { // 성공(0)/미정(1)/실패(2) 여부 반환
    int result = 1;
    int ry = cur_pos.R.first;
    int rx = cur_pos.R.second;
    int by = cur_pos.B.first;
    int bx = cur_pos.B.second;

    switch(dir) {
        case 0: // 상
            if(ry > by) { // B가 위 -> B부터
                while(1) { // B
                    if(by-1 == ry && bx == rx) break; // 기울이기 완료
                    else if(board[by-1][bx] == 'O') return 2; // 실패
                    else if(board[by-1][bx] == '.') by--; // 계속 기울이기
                    else if(board[by-1][bx] == '#') break; // 기울이기 완료
                } // while
                while(1) { // R
                    if(ry-1 == by && rx == bx) break; // 기울이기 완료
                    else if(board[ry-1][rx] == 'O') return 0; // 성공!
                    else if(board[ry-1][rx] == '.') ry--; // 계속 기울이기
                    else if(board[ry-1][rx] == '#') break; // 기울이기 완료
                } // while
            }
            else { // R이 위 -> R부터
                while(1) { // R
                    if(ry-1 == by && rx == bx) break; // 기울이기 완료
                    else if(board[ry-1][rx] == 'O') { ry = rx = -1; result = 0; break; } // 성공!
                    else if(board[ry-1][rx] == '.') ry--; // 계속 기울이기
                    else if(board[ry-1][rx] == '#') break; // 기울이기 완료
                } // while
                while(1) { // B
                    if(by-1 == ry && bx == rx) break; // 기울이기 완료
                    else if(board[by-1][bx] == 'O') return 2; // 실패
                    else if(board[by-1][bx] == '.') by--; // 계속 기울이기
                    else if(board[by-1][bx] == '#') break; // 기울이기 완료
                } // while
            }
            break;
        case 1: // 하
            if(ry < by) { // B가 아래 -> B부터
                while(1) { // B
                    if(by+1 == ry && bx == rx) break; // 기울이기 완료
                    else if(board[by+1][bx] == 'O') return 2; // 실패
                    else if(board[by+1][bx] == '.') by++; // 계속 기울이기
                    else if(board[by+1][bx] == '#') break; // 기울이기 완료
                } // while
                while(1) { // R
                    if(ry+1 == by && rx == bx) break; // 기울이기 완료
                    else if(board[ry+1][rx] == 'O') return 0; // 성공!
                    else if(board[ry+1][rx] == '.') ry++; // 계속 기울이기
                    else if(board[ry+1][rx] == '#') break; // 기울이기 완료
                } // while
            }
            else { // R이 아래 -> R부터
                while(1) { // R
                    if(ry+1 == by && rx == bx) break; // 기울이기 완료
                    else if(board[ry+1][rx] == 'O') { ry = rx = -1; result = 0; break; }// 성공!
                    else if(board[ry+1][rx] == '.') ry++; // 계속 기울이기
                    else if(board[ry+1][rx] == '#') break; // 기울이기 완료
                } // while
                while(1) { // B
                    if(by+1 == ry && bx == rx) break; // 기울이기 완료
                    else if(board[by+1][bx] == 'O') return 2; // 실패
                    else if(board[by+1][bx] == '.') by++; // 계속 기울이기
                    else if(board[by+1][bx] == '#') break; // 기울이기 완료
                } // while
            }
            break;
        case 2: // 좌
            if(rx < bx) { // R이 왼쪽 -> R부터
                while(1) { // R
                    if(ry == by && rx-1 == bx) break; // 기울이기 완료
                    else if(board[ry][rx-1] == 'O') { ry = rx = -1; result = 0; break; } // 성공!
                    else if(board[ry][rx-1] == '.') rx--; // 계속 기울이기
                    else if(board[ry][rx-1] == '#') break; // 기울이기 완료
                } // while
                while(1) { // B
                    if(by == ry && bx-1 == rx) { break; } // 기울이기 완료
                    else if(board[by][bx-1] == 'O') return 2; // 실패
                    else if(board[by][bx-1] == '.') bx--; // 계속 기울이기
                    else if(board[by][bx-1] == '#') break; // 기울이기 완료
                } // while
            }
            else { // B가 왼쪽 -> B부터
                while(1) { // B
                    if(by == ry && bx-1 == rx) break; // 기울이기 완료
                    else if(board[by][bx-1] == 'O') return 2; // 실패
                    else if(board[by][bx-1] == '.') bx--; // 계속 기울이기
                    else if(board[by][bx-1] == '#') break; // 기울이기 완료
                } // while
                while(1) { // R
                    if(ry == by && rx-1 == bx) break; // 기울이기 완료
                    else if(board[ry][rx-1] == 'O') return 0; // 성공!
                    else if(board[ry][rx-1] == '.') rx--; // 계속 기울이기
                    else if(board[ry][rx-1] == '#') break; // 기울이기 완료
                } // while
            }
            break;
        case 3: // 우
            if(rx > bx) { // R이 오른쪽 -> R부터
                while(1) { // R
                    if(ry == by && rx+1 == bx) break; // 기울이기 완료
                    else if(board[ry][rx+1] == 'O') { ry = rx = -1; result = 0; break; } // 성공!
                    else if(board[ry][rx+1] == '.') rx++; // 계속 기울이기
                    else if(board[ry][rx+1] == '#') break; // 기울이기 완료
                } // while
                while(1) { // B
                    if(by == ry && bx+1 == rx) break; // 기울이기 완료
                    else if(board[by][bx+1] == 'O') return 2; // 실패
                    else if(board[by][bx+1] == '.') bx++; // 계속 기울이기
                    else if(board[by][bx+1] == '#') break; // 기울이기 완료
                } // while
            }
            else { // B가 오른쪽 -> B부터
                while(1) { // B
                    if(by == ry && bx+1 == rx) break; // 기울이기 완료
                    else if(board[by][bx+1] == 'O') return 2; // 실패
                    else if(board[by][bx+1] == '.') bx++; // 계속 기울이기
                    else if(board[by][bx+1] == '#') break; // 기울이기 완료
                } // while
                while(1) { // R
                    if(ry == by && rx+1 == bx) break; // 기울이기 완료
                    else if(board[ry][rx+1] == 'O') return 0; // 성공!
                    else if(board[ry][rx+1] == '.') rx++; // 계속 기울이기
                    else if(board[ry][rx+1] == '#') break; // 기울이기 완료
                } // while
            }
            break;
    } // switch

    nxt_pos = {{ry, rx}, {by, bx}};

    return result;
}

int main() {
    int N, M;
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];
            if(board[i][j] == 'R') {
                board[i][j] = '.';
                R_pos = {i, j};
            }
            else if(board[i][j] == 'B') {
                board[i][j] = '.';
                B_pos = {i, j};
            }
       } // for j
    } // for i

    int ans = 0;
    queue<pos> q;
    q.push({R_pos, B_pos});

    while(!q.empty()) {
        ans++;
        if(ans > 10) break;

        int size = q.size();
        for(int h = 0; h < size; h++) {
            pos cur_pos = q.front();
            q.pop();
            for(int i = 0; i < 4; i++) {
                pos nxt_pos;
                int flag = tilt(cur_pos, nxt_pos, i);
                if(flag == 0) { // 성공
                    // 프로그램 종료
                    cout << ans;
                    return 0;
                } 
                else if(flag == 1) { // 미정
                    // q에 push
                    q.push(nxt_pos);
                }
                else { // 실패
                    // do nothing
                }
            } // for i
        } // for h
    } // while

    cout << -1;

    return 0;
}