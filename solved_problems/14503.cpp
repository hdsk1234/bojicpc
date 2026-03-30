#include <iostream>
using namespace std;

// 전역변수 선언
int blocks[50][50]; // 0: 청소x, 1: 벽, 2: 청소o

int front_block(int y, int x, int d)
{
    switch (d)
    {
    case 0:
        return blocks[y - 1][x];
    case 1:
        return blocks[y][x + 1];
    case 2:
        return blocks[y + 1][x];
    case 3:
        return blocks[y][x - 1];
    }
} // front_block()

int back_block(int y, int x, int d)
{
    switch (d)
    {
    case 0:
        return blocks[y + 1][x];
    case 1:
        return blocks[y][x - 1];
    case 2:
        return blocks[y - 1][x];
    case 3:
        return blocks[y][x + 1];
    }
} // back_block()

void move_front_block(int &y, int &x, int d)
{
    switch (d)
    {
    case 0:
        y--;
        break;
    case 1:
        x++;
        break;
    case 2:
        y++;
        break;
    case 3:
        x--;
        break;
    }
} // move_front_block()

void move_back_block(int &y, int &x, int d)
{
    switch (d)
    {
    case 0:
        y++;
        break;
    case 1:
        x--;
        break;
    case 2:
        y--;
        break;
    case 3:
        x++;
        break;
    }
} // move_back_block()

int main()
{
    // 변수 선언
    int N, M;
    int r, c;
    int d; // 0: 북, 1: 동, 2: 남, 3: 서
    int cur_y, cur_x, cur_d;
    int ans = 0;

    // 입력
    cin >> N >> M;
    cin >> r >> c >> d;
    cur_y = r; cur_x = c; cur_d = d;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> blocks[i][j];
        } // for j
    } // for i


    // 로직
    while (1)
    {
        if (!blocks[cur_y][cur_x])
        { // 1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
            blocks[cur_y][cur_x] = 2;
            ans++;
        }

        if (blocks[cur_y - 1][cur_x] && blocks[cur_y + 1][cur_x] && blocks[cur_y][cur_x - 1] && blocks[cur_y][cur_x + 1])
        { // 2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,

            if (back_block(cur_y, cur_x, cur_d) != 1)
            { // 2-1. 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
                move_back_block(cur_y, cur_x, cur_d);
                continue;
            }
            else
            { // 2-2. 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
                break;
            }
        }

        if (!blocks[cur_y - 1][cur_x] || !blocks[cur_y + 1][cur_x] || !blocks[cur_y][cur_x - 1] || !blocks[cur_y][cur_x + 1])
        { // 3. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우

            cur_d = (cur_d + 3) % 4; // 3-1. 반시계 방향으로 90도 회전한다.

            if (front_block(cur_y, cur_x, cur_d) == 0)
            { // 3-2. 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
                move_front_block(cur_y, cur_x, cur_d);
            }

            continue; // 3-3. 1번으로 돌아간다.
        }
    } // while

    cout << ans;
    return 0;
}