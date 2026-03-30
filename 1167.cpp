#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int num;
    int distance;
};


vector< Node > adjacent[10001];
bool visited[10001];
int max = -1;
int curmax = 0;


Node dfs(Node cur) { // 가장 먼 노드를 반환
    curmax += cur.distance;

    visited[cur.num] = true;

    for(int i = 0; i < adjacent[cur.num].size(); i++) {
        Node next = adjacent[cur.num][i];
        if(!visited[next.num]) dfs(next);
    } // for i



} // dfs()

int main() {
    int V;
    cin >> V;
    for(int i = 0; i < V; i++) {
        int a;
        cin >> a; 
        while(1) {
            int b, c;
            cin >> b;
            if (b == -1) break;
            cin >> c;
            Node n = {b, c};
            adjacent[a].push_back({b, c});
        } // while
    } // for i

    fill_n(visited, 10001, false);
    Node leaf_node = dfs({1, 0});

    fill_n(visited, 10001, false);
    Node ans = dfs(leaf_node);

    cout << ans.distance;

    return 0;
}