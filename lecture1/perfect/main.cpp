#include <iostream>
using namespace std;

int main() {
  int found = 0; // How many perfect numbers we've found
  int number = 1; // Next number to test

  /* Keep looking until we've found four perfect numbers. */
  while (found < 4) {

    /* Calculate the sum of the positive divisors of the number n >= 0. */
    int total = 0;
    for (int i = 1; i < number; i++) {
      if (number % i == 0) {
      total += i;
      }
    }

    /* A number is perfect if the sum of its divisors is equal to it. */
    if (total == number) {
      cout << number << endl;
      found++;
    }
    number++;
  }

  return 0;
}
