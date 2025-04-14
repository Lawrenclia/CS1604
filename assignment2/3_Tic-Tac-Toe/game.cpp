#include "game.h"

#include <iostream>
using namespace std;

long long play(long long code, int player, int x, int y) {
  // Your code here
  int multi;
  if (x == 1 && y == 1) {multi = 2;
  } else if (x == 1 && y == 2) { multi = 3;
  } else if (x == 1 && y == 3) { multi = 5;
  } else if (x == 2 && y == 1) { multi = 7;
  } else if (x == 2 && y == 2) { multi = 11;
  } else if (x == 2 && y == 3) { multi = 13;
  } else if (x == 3 && y == 1) { multi = 17;
  } else if (x == 3 && y == 2) { multi = 19;
  } else{ multi = 23;
  }
  if (player == 1) {code *= multi;
  } else { code *= (multi * multi);
  } return code;
}

void print(long long code) {
  // Your code here
  if (code % 2 != 0) cout << "- " ;
  else if (code % 4 == 0) cout << "O ";
  else cout << "X ";
  if (code % 3 != 0) cout << "- ";
  else if (code % 9 == 0) cout << "O ";
  else cout << "X ";
  if (code % 5 != 0) cout << "-";
  else if (code % 25 == 0) cout << "O";
  else cout << "X";
  cout << endl;
  if (code % 7 != 0) cout << "- ";
  else if (code % 49 == 0) cout << "O ";
  else cout << "X ";
  if (code % 11 != 0) cout << "- ";
  else if (code % 121 == 0) cout << "O ";
  else cout << "X ";
  if (code % 13 != 0) cout << "- ";
  else if (code % 169 == 0) cout << "O";
  else cout << "X";
  cout << endl;
  if (code % 17 != 0) cout << "- ";
  else if (code % 289 == 0) cout << "O ";
  else cout << "X ";
  if (code % 19 != 0) cout << "- ";
  else if (code % 361 == 0) cout << "O ";
  else cout << "X ";
  if (code % 23 != 0) cout << "- ";
  else if (code % 529 == 0) cout << "O";
  else cout << "X";
}

bool detern(long long code, int divisor1, int divisor2, int divisor3) {
    return code % divisor1 == 0 && code % divisor2 != 0 && code % divisor3 != 0;
}

int check_winner(long long code) {
    // Your code here
    if (code % 11 == 0 && code % 121 != 0 && ( detern(code, 46, 4, 529) || detern(code, 85, 25, 289) ||
                                                detern(code, 91, 49, 169) || detern(code, 57, 9, 361)))
            return 1;
    else if (code % 2 == 0 && code % 4 != 0 &&( detern(code, 15, 9, 25) || detern(code, 119, 49, 289)))
            return 1;
    else if (code % 23 == 0 && code % 529 != 0 &&( detern(code, 65, 25, 169) || detern(code, 323, 289, 361)))
            return 1;
    else if ((code % 121 == 0) &&(code % 2116 == 0 || code % 7225 == 0 || code % 3249 == 0 || code % 8281 == 0))
            return 2;
    else if ((code % 4 == 0) && (code % 225 == 0 || code % 14161 == 0))
            return 2;
    else if ((code % 529 == 0) && (code % 4225 == 0 || code % 104329 == 0))
            return 2;
    else return 0;
}
