#include <iostream>

#include "game.h"
using namespace std;

int main() {
  int n;
  cin >> n;
  long long cur_code = 1;
  int cur_p = 1;
  for (int i = 0; i < n; ++i, cur_p = 3 - cur_p) {
    int x, y;
    cin >> x >> y;
    cur_code = play(cur_code, cur_p, x, y);
    cout << cur_code << endl;
    print(cur_code);
    cout << endl;
    int winner = check_winner(cur_code);
    if (winner) {
      cout << "Player" << winner << " wins!" << endl;
      return 0;
    }
  }
  cout << "Draw." << endl;
  return 0;
}