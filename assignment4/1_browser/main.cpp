#include <iostream>
#include <string>
#include <stack>
#include "utilities.h"
using namespace std;

void visitURL(stack<string>& url1, stack<string>& url2, string& cmd) {
    string url = cmd.substr(6);
    url1.push(url);
    url2 = stack<string>();
}

void backURL(stack<string>& url1, stack<string>& url2, string& cmd) {
    if (url1.size() > 1) {
        string temp = url1.top();
        url1.pop();
        url2.push(temp);
    }
}

void forwardURL(stack<string>& url1, stack<string>& url2, string& cmd) {
    if (url2.size()) {
        string temp = url2.top();
        url2.pop();
        url1.push(temp);
    }
}

void currentURL(stack<string>& url1) {
    if (url1.size()) {
        cout << url1.top() << endl;
    }
}

int main(){
    int n;
    stack<string> url1;
    stack<string> url2;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        string cmd;
        getline(cin, cmd);
        if (cmd == "current") {
            currentURL(url1);
        } else if (cmd.substr(0,5) == "visit") {
            visitURL(url1, url2, cmd);
        } else if (cmd == "back") {
            backURL(url1, url2, cmd);
        } else if (cmd == "forward") {
            forwardURL(url1, url2, cmd);
        } else {
            cout << "Error Input" << endl;
            return 0;
        }
    }
    return 0;
}
