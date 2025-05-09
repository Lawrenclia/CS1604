#include <iostream>
using namespace std;

int cmp(int num1, int num2) {
  if (num1 == num2) return 0;
  else if (num1 == 42) return 1;
  else if (num2 == 42) return -1;
  else if (num1 % 5 == 0 && num1 % 10 != 0 && (num2 % 5 != 0 || num2 % 10 == 0)) return 1;
  else if (num2 % 5 == 0 && num2 % 10 != 0 && (num1 % 5 != 0 || num1 % 10 == 0)) return -1;
  else if (num1 % num2 == 0) return -1;
  else if (num2 % num1 == 0) return 1;
  else if (num1 % 2 != 0 && num1 % 3 != 0 && num1 % 5 != 0 && num1 % 7 == 0 &&
            (num2 % 2 == 0 || num2 % 3 == 0 || num2 % 5 == 0 || num2 % 7 != 0)) return 1;
  else if (num2 % 2 != 0 && num2 % 3 != 0 && num2 % 5 != 0 && num2 % 7 == 0 &&
            (num1 % 2 == 0 || num1 % 3 == 0 || num1 % 5 == 0 || num1 % 7 != 0)) return 1;
  else if (num1 > num2) return 1;
  else return -1;
}


int main() {
  int num1, num2;
  cin >> num1 >> num2;
  cout << cmp(num1, num2) << endl;
  return 0;
}
