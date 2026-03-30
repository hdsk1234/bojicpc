#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    for(int testcase = 0; testcase < T; testcase++) {
        // 변수 선언
        int N, M;
        queue< pair<int, int> > q; // (문서번호, 중요도)
        vector<int> priorities;
        int ans = 0;

        // 입력
        cin >> N >> M; 
        for(int i = 0; i < N; i++) {
            int priority; 
            cin >> priority;
            q.push(make_pair(i, priority));
            priorities.push_back(priority);
        } // for i
    
        sort(priorities.begin(), priorities.end());

        // 풀이
        while(1) {
            int cur_num = q.front().first;
            int cur_priority = q.front().second;
            if(cur_priority == priorities.back()) {
                ans++;
                priorities.pop_back();
                if(cur_num == M) {
                    cout << ans << '\n';
                    break;
                }
            } else {
                q.push(q.front());
            }
            q.pop();
        } // while
    } // for testcase

    return 0;
}