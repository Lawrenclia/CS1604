#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "utilities.h"
using namespace std;
typedef pair<int, int> point;

bool notwall(int numRow, int numCol, int row, int col, vector<string>& grid, vector<vector<int>>& found) {
    return row >= 0 && row < numRow && col >= 0 && col < numCol && !found[row][col] && grid[row][col] != 'W';
}

void reach(int numRow,int numCol,int numEnt, const vector<point>& entrance, vector<string>& grid) {
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < numEnt; ++i) {
        point p = entrance[i];
        vector<vector<int>> found(numRow,vector<int>(numCol, false));
        queue<point> que;
        if (grid[p.first][p.second] == '.') {
            que.push(p);
            found[p.first][p.second] = true;
        }
        bool reachable = false;
        while (!que.empty()){
            point p1 = que.front();
            que.pop();
            int pfirst = p1.first;
            int psecond = p1.second;
            if (pfirst == numRow-1 && psecond == numCol-1) {
                reachable = true;
                break;
            }

            for (const auto& dir : directions) {
                int newRow = p1.first + dir.first;
                int newCol = p1.second + dir.second;
                if (notwall(numRow, numCol, newRow, newCol, grid, found)) {
                    que.push({newRow, newCol});
                    found[newRow][newCol] = true;
                }
            }
        }
        if (reachable) {
            cout << "reachable" << endl;
        } else {
            cout << "unreachable" << endl;
        }
    }

}
int main(){
    int numRow;
    int numCol;
    int numEnt;
    vector<point> entrance;
    vector<string> grid;
    cin >> numRow >> numCol >> numEnt;
    for (int i = 0; i < numEnt; ++i) {
        point p;
        cin >> p.first >> p.second;
        entrance.push_back(p);
    }
    cin.ignore();
    for (int j = 0; j < numRow; ++j) {
        string row;
        getline(cin, row);
        grid.push_back(row);
    }
    reach(numRow, numCol, numEnt, entrance, grid);
    return 0;
}
