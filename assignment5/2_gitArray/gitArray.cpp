#include "gitArray.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

GitArray::GitArray(int length) {
    std::vector<std::vector<int>> gitMain;
    gitMain.push_back(vector<int>(length, 0));
    branches["main"] = gitMain;
    name = "main";
    line = 0;
}

std::string GitArray::toString() {
    string result = "(";
    for (int i = 0; i < branches[name][line].size(); ++i) {
        string num = to_string(branches[name][line][i]);
        result = result + num + ",";
    }
    result.pop_back();
    result += ")";
    return result;
}

void GitArray::set(int index, int value) {
    int t = branches[name].size();
    if (line < t - 1) {
        branches[name].erase(branches[name].begin() + line + 1, branches[name].end());
    }
    branches[name].push_back(branches[name][line]);
    ++line;
    branches[name][line][index] = value;
}

int GitArray::get(int index, int version) {
    return branches[name][line + version][index];
}

void GitArray::undo() {
    if (line <= 0) {
        cout << "No Previous Version to Undo" << endl;
    } else {
        --line;
    }
}

void GitArray::redo() {
    if (line >= branches[name].size() - 1) {
        cout << "No Next Version to Redo" <<endl;
    } else {
        ++line;
    }
}

void GitArray::branch(const std::string& branch_name) {
    vector<vector<int>> other;
    other = branches[name];
    branches[branch_name] = other;
}

void GitArray::checkout(const std::string& branch_name) {
    if (branches.count(branch_name) == 0) {
        cout << "Branch not found" << endl;
    } else {
        name = branch_name;
        line = branches[name].size() - 1;
    }
}
