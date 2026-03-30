#include <iostream>
using namespace std;

int main() {
    long long a, b, c;
    cin >> a >> b >> c;

    int ans = 1;

    while(b > 0) {
        if(b % 2 == 1) {
            ans = (ans*a)%c;
            b--;
        }
        
        a = (a*a)%c;
        b /= 2;
    }
    cout << ans;
    return 0;
}