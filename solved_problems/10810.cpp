#include <iostream>
using namespace std;

int boxes[101];

int main() {
    int N, M;
    cin >> N >> M;
    for(int h = 0; h < M; h++) {
        int i, j, k;
        cin >> i >> j >> k;
        for(int l = i; l <= j; l++) boxes[l] = k;
    } // for h

    for (int i = 1; i <= N; i++) cout << boxes[i] << " ";
}