#include <iostream>
#include <sstream>
#include "gitArray.h"
#include <string>
using namespace std;

int main()
{
	// The git array
	GitArray arr(0);
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string command;
        iss >> command;
        if (isdigit(command[0])) {
            int length = stoi(command);
            arr = GitArray(length);
        } else if (command == "print") {
            string res = arr.toString();
            cout << res <<endl;
        } else if (command == "set") {
            int index, value;
            iss >> index >> value;
            arr.set(index, value);
        } else if (command == "get") {
            int index, value;
            iss >> index >> value;
            int res = arr.get(index, value);
            cout << res << endl;
        } else if (command == "undo") {
            arr.undo();
        } else if (command == "redo") {
            arr.redo();
        } else if (command == "branch") {
            string branch_name;
            iss >>branch_name;
            arr.branch(branch_name);
        } else if (command == "checkout") {
            string branch_name;
            iss >>branch_name;
            arr.checkout(branch_name);
        }
    }
	return 0;
}
