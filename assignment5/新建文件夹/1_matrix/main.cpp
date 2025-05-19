#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "matrix.h"

using namespace std;

int main() {
    // Store the matrices
    map<string, Matrix> mats;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string command;
        iss >> command;
        if (command == "new") {
            string name;
            int row, col;
            iss >> name >> row >> col;
            mats[name] = Matrix(row, col);
        } else if (command == "set") {
            string name;
            int row, col, val;
            iss >> name >> row >> col >> val;
            if (mats.count(name) > 0) {
                mats[name].set(row, col, val);
            }
        } else if (command == "get") {
            string name;
            int row, col;
            iss >> name >> row >> col;
            if (mats.count(name) > 0) {
                cout << mats[name].get(row, col) << std::endl;
            }
        } else if (command == "add") {
            string A, B, C;
            iss >> A >> B >> C;
            if (mats.count(A) > 0 && mats.count(B) > 0) {
                mats[C] = mats[A] + mats[B];
            }
        } else if (command == "mul") {
            string A, B, C;
            iss >> A >> B >> C;
            if (mats.count(A) > 0 && mats.count(B) > 0) {
                mats[C] = mats[A] * mats[B];
            }
        } else if (command == "print") {
            std::string name;
            iss >> name;
            if (mats.count(name) > 0) {
                cout << mats[name];
            }
        } else if (command == "error") {
            string name;
            iss >> name;
            if (mats.count(name) > 0) {
            int num = mats[name].getErrorCode();
            if (num == 0) {
                cout << "No Error" << endl;
            } else if (num == 1) {
                cout << "Index out of Range" << endl;
            } else if (num == 2) {
                cout << "Dimension Mismatch" << endl;
            } else {
                cout << "Invalid Dimension" << endl;
                }
            }
        }
    }
    return 0;
}
