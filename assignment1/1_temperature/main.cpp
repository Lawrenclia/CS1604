#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double f_temp;
    double c_temp;
    cin >> f_temp;
    c_temp = 5.0*(f_temp - 32)/9.0;
    cout << fixed << setprecision(2) << c_temp << endl;
    return 0;
}
