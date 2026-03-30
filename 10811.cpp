#include <iostream>
#include <numeric>
using namespace std;

int main() {
    int boxes[101];
    iota(boxes, boxes+101, 0);

    int N, M;
    cin >> N >> M;
    for(int h = 0; h < M; h++) {
        int i, j;
        cin >> i >> j;
        int mid = (i+j)/2;

        for(int k = i; k <= mid; k++) {
            int start = k;
            int end = j+i-k;
            int t = boxes[start];
            boxes[start] = boxes[end];
            boxes[end] = t;
        } // for k

    } // for h

    for(int i = 1; i <= N; i++) cout << boxes[i] << " ";
    return 0;
}