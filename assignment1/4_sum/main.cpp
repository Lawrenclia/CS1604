#include <iostream>
using namespace std;

int main()
{
    int m, n, sum1, sum2;
    cin >> m >> n;
    sum1 = 0;
    sum2 = 0;
    int divisor = 2;
    while (m > 1){
        if (m%divisor == 0){
            sum1 += divisor;
            m /= divisor;
        }else divisor += 1;
    }

    divisor = 2;
    while (n > 1){
        if (n%divisor == 0){
            sum2 += divisor;
            n /= divisor;
        }else divisor += 1;
    }
    if (sum1 == sum2) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;

}
