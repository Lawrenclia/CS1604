#include <iostream>
using namespace std;

bool match(int x1, int x2) { return ((x1 + 10) ^ 0xaaa) > ((x2 + 10) ^ 0xaaa); }

int main() {
  // Your code here
  int n = 0;
  int num_1 = 0;
  int num_2 = 0;
  int num_3 = 0;
  int temp_num = 0;
  cin >> n;

  cin >> num_1;
  cin >> temp_num;
  if (match(num_1, temp_num)) {
    num_2 = temp_num;
  } else {
      num_2 = num_1;
      num_1 = temp_num;
  }

  cin >> temp_num;
  if (match(temp_num, num_1)) {
        num_3 = num_2;
        num_2 = num_1;
        num_1 = temp_num;
    } else if (match(temp_num, num_2)) {
        num_3 = num_2;
        num_2 = temp_num;
    } else num_3 = temp_num;

  for (int i = 3; i < n; ++i) {
    cin >> temp_num;
    if (match(temp_num, num_1)) {
        num_3 = num_2;
        num_2 = num_1;
        num_1 = temp_num;
    } else if (match(temp_num, num_2)) {
        num_3 = num_2;
        num_2 = temp_num;
    } else if (match(temp_num, num_3)) {
        num_3 = temp_num;
    } else continue;
  }
  cout << num_1 << " "<< num_2 << " " << num_3 << endl;
}
