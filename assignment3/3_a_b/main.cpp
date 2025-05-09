#include <iostream>
#include <vector>
#include <string>
using namespace std;

void use(string& str, string& t) {
    size_t equa = t.find('=');
    string bef = t.substr(0, equa);
    size_t nBef = bef.length();
    string aft = t.substr(equa + 1);
    if (str.find(bef) != string::npos) {
        str.replace(str.find(bef), nBef, aft);
        cout << str << endl;
    }
}
bool usable(string& str, string& t) {
    size_t equa = t.find('=');
    string bef = t.substr(0, equa);
    if (str.find(bef) != string::npos) {
        return true;
    } else {return false;}
}

int main() {
    string str;
    string t;
    cin >> str;
    cout << str << endl;
    vector<string> instruct;

    int counter = 0;
    while (cin >> t) {
        instruct.push_back(t);
        ++counter;
    }
    bool flag = true;
    while (flag){
        for (int i = 0; i < counter; ++i) {
            if (usable(str, instruct[i])) {
                use(str,instruct[i]);
                flag = true;
                break;
            }
        flag = false;
        }
    }
    return 0;
}
