#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <cctype>
#include <algorithm>
#include "utilities.h"
using namespace std;

void separate(vector<string>& commands, string& command) {
    size_t sign = 0;
    if (command.find(' ') != string::npos) {
        sign = command.find(' ');
        commands.push_back(command.substr(0, sign));
        commands.push_back(command.substr(sign + 1));
    } else {
        commands.push_back(command);
        commands.push_back("");
    }
}

string findtype(string& instruct) {
    if (instruct == "Sleep") return "00";
    if (instruct == "Add") return "10";
    if (instruct == "Sub") return "11";
    if (instruct == "Mul") return "12";
    if (instruct == "Div") return "13";
    if (instruct == "Assign") return "20";
    if (instruct == "Var") return "21";
    if (instruct == "Const") return "22";
    if (instruct == "Jmp") return "30";
    if (instruct == "JmpEq") return "31";
    if (instruct == "JmpGt") return "32";
    if (instruct == "JmpLt") return "33";
    if (instruct == "Input") return "40";
    if (instruct == "Output") return "41";
    return "";
}

void sleep(string& number, int& clock, int& level, int t){
    int num = stoi(number);
    int repeat = min(num, t-clock);
    for (int i = 0; i < repeat; ++i) {
        cout << level << ' ';
    }
    clock += repeat;
}

void calcu1(string& type, stack<int>& Stack) {
    int num1 = Stack.top();
    Stack.pop();
    int num2 = Stack.top();
    Stack.pop();
    int num3;
    if (type[1] == '0') num3 = num1 + num2;
    if (type[1] == '1') num3 = num2 - num1;
    if (type[1] == '2') num3 = num1 * num2;
    if (type[1] == '3') num3 = num2 / num1;
    Stack.push(num3);
}

void calcu2(string& type, string& number, stack<int>& Stack, map<string, int>& State) {
    if (type[1] == '0') {
        int num = Stack.top();
        Stack.pop();
        State[number] = num;
    } else if (type[1] == '1' && State.count(number)) {
        int num1 = State[number];
        Stack.push(num1);
    } else if (type[1] == '2') {
        int num2 = stoi(number);
        Stack.push(num2);
    }
}

void jump(string& type, string& number, stack<int>& Stack, int& pc) {
    int num = stoi(number);
    if (type[1] == '0') {
        pc = num;
    } else {
        int num1 = Stack.top();
        Stack.pop();
        int num2 = Stack.top();
        Stack.pop();
        if ((type[1] == '1' && num1 == num2) || (type[1] == '2' && num1 < num2) || (type[1] == '3' && num1 > num2)) {
            pc = num;
        } else {
            pc++;
        }
    }
}

void program(int n, int t, vector<string>& commands, vector<int>& times) {
    int pc = 0;
    int clock = 0;
    int level = 0;
    stack<int> Stack;
    map<string, int> State;
    while (clock < t) {
        string instruct = commands[2*pc];
        string number = commands[2*pc + 1];
        string type = findtype(instruct);
        if (type[0] == '0') {
            sleep(number, clock, level,t);
            pc++;
        } else if (type[0] == '1') {
            calcu1(type, Stack);
            pc++;
        } else if (type[0] == '2') {
            calcu2(type, number, Stack, State);
            pc++;
        } else if (type[0] == '3') {
            jump(type, number, Stack, pc);
        } else if (type == "40") {
            Stack.push(times[clock]);
            pc++;
        } else if (type == "41") {
            if (isdigit(number[0])) {
                level = stoi(number);
            } else {
                level = State[number];
            }
            pc++;
        }
        if (pc == n) {
            pc = 0;
        }
    }
    cout << endl;
}

int main(){
    int n, t;
    cin >> n >> t;
    cin.ignore();
    vector<string> commands;
    for (int i = 0; i < n; ++i) {
        string command;
        getline(cin, command);
        separate(commands,command);
    }
    vector<int> times;
    for (int i = 0; i < t; ++i) {
        int time;
        cin >> time;
        times.push_back(time);
    }
    program(n, t, commands, times);
    return 0;
}
