#include <iostream>
using namespace std;

struct Node
{
    char value;
    char left;
    char right;
};

Node arr[26];

void preorder(char c) {
    if(c == '.') return;

    cout << c;
    preorder(arr[c-'A'].left);
    preorder(arr[c-'A'].right);
}

void inorder(char c) {
    if(c == '.') return;

    inorder(arr[c-'A'].left);
    cout << c;
    inorder(arr[c-'A'].right);
}

void postorder(char c) {
    if(c == '.') return;

    postorder(arr[c-'A'].left);
    postorder(arr[c-'A'].right);
    cout << c;
}


int main () {
    int N;
    cin >> N;

    for(int i = 0; i < N; i++) {
        char v, l, r;
        cin >> v >> l >> r;

        arr[v-'A'].value = v;
        arr[v-'A'].left = l;
        arr[v-'A'].right = r;
    }
   
    preorder('A');
    cout << endl;
    inorder('A');
    cout << endl;
    postorder('A');

    return 0;
}