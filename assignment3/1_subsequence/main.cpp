#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void findStr (string& s, string& t) {
    int flag = 1;
    int j = 0;
    int sLength = s.length();
    int tLength = t.length();
    for (int i = 0; i < sLength; ++i) {
        while (tolower(t[j]) != tolower(s[i]) && j < tLength) {
            j += 1;
        }
        if (j < tLength) {
            j += 1;
            continue;
        } else {
            flag = 0;
        break;
        }
    }
    if (flag) {
        cout << t << endl;
    }
}



int main() {
    string s;
    cin >> s;
    string t;
    while(cin >> t){
        findStr(s, t);
    }
    return 0;
}
