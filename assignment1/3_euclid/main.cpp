#include <iostream>
using namespace std;

int main()
{
    int m,n,remainder;
    cin >> m >> n;
    if (m <= n) {
        int p = m;
        m = n;
        n = p;
    };
    remainder = 1;

    while (remainder > 0){
        remainder = m % n;
        cout << n << ' ';
        m = n;
        n = remainder;
    }
    return 0;
}
