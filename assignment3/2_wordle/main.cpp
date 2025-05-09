#include <iostream>
#include <string>
using namespace std;

string toUpper(string& str) {
    string upper = "";
    for (size_t i = 0; i < str.length(); ++i) {
        upper += toupper(str[i]);
    }
    return upper;
}

string detAns(string& ans, string& guess) {
    string outPut = "";
    string ansUpper = toUpper(ans);
    string guessUpper = toUpper(guess);
    for (size_t i = 0; i < ans.length(); ++i) {
        if (ansUpper[i] == guessUpper[i]) {
            outPut += 'g';
        } else {
            outPut += 'n';
        }
    }
    for (size_t i = 0; i < guess.length(); ++i) {
        if (outPut[i] == 'g') {
            guessUpper[i] = ' ';
            ansUpper[i] = ' ';
        }
    }

    for (size_t i = 0; i < guess.length(); ++i) {
        if ((guessUpper[i] != ' ')&&(ansUpper.find(guessUpper[i]) != string::npos)) {
            outPut[i] = 'y';
        }
    }

    return outPut;
}




int main() {
    string ans;
    string guess;
    cin >> ans;

    int tryTime = 0;
    while (cin >> guess && tryTime < 6) {
        detAns(ans, guess);
        cout << detAns(ans, guess) << endl;
        if (detAns(ans, guess) == "ggggg") {
            cout << "won" << endl;
            break;
        } else if (tryTime == 5) {
            cout << "The answer is " << toUpper(ans) << endl;
        }
        tryTime += 1;
    }
    return 0;
}
