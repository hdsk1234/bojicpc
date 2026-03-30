#include <iostream>
#include <numeric>
using namespace std;

int boxes[101];

int main() {
    int N, M;
    cin >> N >> M;
    iota(boxes, boxes+101, 0);
    for(int h = 0; h < M; h++) {
        int i, j;
        cin >> i >> j;
        int t = boxes[i];
        boxes[i] = boxes[j];
        boxes[j] = t;
    } // for h
    
    for(int i = 1; i <= N; i++) cout << boxes[i] << " ";
}