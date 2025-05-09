#include <iostream>
using namespace std;

int main()
{
    int n, x, y, z;
    cin >> n;

    x = n/1440;
    if (x > 0) cout << x << 'd';

    y = (n - 1440*x)/60;
    if (y > 0) cout << y << 'h';
    z = n - 1440*x - 60*y;
    if (z > 0) cout << z << 'm';
    return 0;

}
