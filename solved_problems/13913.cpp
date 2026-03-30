#include <iostream>
#include <queue>
using namespace std;

int visited[100001];
int moved[100001]; // move[17]에는 어디에서 17로 왔는지 기록. 
vector<int> ans;

int main() {
    int N, K;
    cin >> N >> K;

    int time = 0;
    queue<int> q;
    q.push(N);

    while(1) {
        int size = q.size();

        for(int i = 0; i < size; i++) {
            int cur = q.front();
            visited[cur] = 1;

            if(cur == K) {
                cout << time << endl;

                int t = K;
                while(t != N) {
                    ans.push_back(t);
                    t = moved[t];
                } // while
                ans.push_back(N);

                for(int i = ans.size()-1; i >= 0; i--) {
                    cout << ans[i] << " ";
                }

                return 0;
            }

            if(cur-1 >= 0 && !visited[cur-1]) {
                q.push(cur-1);
                moved[cur-1] = cur;
                visited[cur-1] = 1;
            }

            if(cur+1 <= 100000 && !visited[cur+1]) {
                q.push(cur+1);
                moved[cur+1] = cur;
                visited[cur+1] = 1;
            }

            if(cur*2 <= 100000 && !visited[cur*2]) {
                q.push(cur*2);
                moved[cur*2] = cur;
                visited[cur*2] = 1;
            }

            q.pop();

        } // for i
        time++;
    } // while

    return 0;
}