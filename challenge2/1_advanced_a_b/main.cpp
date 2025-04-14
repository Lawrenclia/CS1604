#include <iostream>
#include <vector>
#include <string>
using namespace std;


bool equa(string& str, string& t, size_t& sign) {
    string before = t.substr(0, sign);
    if (str.find(before) != string::npos) {
        string after = t.substr(sign + 1);
        str.replace(str.find(before), before.length(), after);
        cout << str << endl;
        return true;
    } else return false;
}

bool equaReturn(string& str, string& t, size_t& sign) {
    string before = t.substr(0, sign);
    if (str.find(before) != string::npos) {
        cout << t.substr(sign + 9) << endl;
        return true;
    } else return false;
}

bool equaStart(string& str, string& t, size_t& sign) {
    string before = t.substr(0, sign);
    if (str.find(before) != string::npos) {
        str.erase(str.find(before),before.length());
        str = t.substr(sign + 8) + str;
        cout << str << endl;
        return true;
    } else return false;
}

bool equaEnd(string& str, string& t, size_t& sign) {
    string before = t.substr(0, sign);
    if (str.find(before) != string::npos) {
        str.erase(str.find(before),before.length());
        str = str + t.substr(sign + 6);
        cout << str << endl;
        return true;
    } else return false;
}

bool startEqua(string& str, string& t, size_t& sign) {
    string before = t.substr(7, sign - 7);
    if (str.find(before) == 0) {
        if (t[sign + 1] == '(') {
            str = str.substr(before.length()) + t.substr(sign + 6);
        } else {
            str = t.substr(sign + 1) + str.substr(before.length());
        }
        cout << str << endl;
        return true;
    } else return false;
}

bool endEqua(string& str, string& t, size_t& sign) {
    string before = t.substr(5, sign - 5);
    size_t sl = str.length();
    size_t bl = before.length();
    if (str.substr(sl - bl) == before) {
        if (t[sign + 1] == '(') {
            str = t.substr(sign + 8) + str.substr(0, sl - bl);
        } else {
            str = str.substr(0, sl - bl) + t.substr(sign + 1);
        }
        cout << str << endl;
        return true;
    } else return false;
}

bool allocate(string& str, string& t, size_t& sign);

bool onceEqua(string& str, string&t, size_t& sign) {
    string subInstr = t.substr(6);
    size_t subSign = sign - 6;
    if (allocate(str, subInstr, subSign)) {
        return true;
    } else return false;
}

bool allocate(string& str, string& t, size_t& sign) {
    if (t.substr(0, 6) == "(once)") {
        return onceEqua(str, t, sign);
    } else if (t.substr(0, 7) == "(start)") {
        return startEqua(str, t, sign);
    } else if (t.substr(0, 5) == "(end)") {
        return endEqua(str, t, sign);
    } else if (t.substr(sign + 1, 7) == "(start)") {
        return equaStart(str, t, sign);
    } else if (t.substr(sign + 1, 5) == "(end)") {
        return equaEnd(str, t, sign);
    } else if (t.substr(sign + 1, 8) == "(return)") {
        return equaReturn(str, t, sign);
    } else return equa(str, t, sign);
}


int main() {
    string str;
    string t;
    cin >> str;
    vector<string> instruct;
    int counter = 0;
    while (cin >> t) {
        instruct.push_back(t);
        ++counter;
    }
    cout << str << endl;
    bool flag = true;
    while (flag){
        for (int i = 0; i < counter; ++i) {
            string instr = instruct[i];
            size_t sign = instr.find('=');
            if (allocate(str, instr, sign)) {
                if (instr.substr(sign + 1, 8) == "(return)") {
                    flag = false;
                } else if (instr.substr(0, 6) == "(once)") {
                    instruct.erase(instruct.begin() + i);
                    counter -= 1;
                    flag = true;
                } else {
                    flag = true;
                }
                break;
            }
            flag = false;
        }
    }
    return 0;
}
