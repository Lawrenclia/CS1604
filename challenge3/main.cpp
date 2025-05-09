#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"                 // Required for GUI controls

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <map>

using namespace std;

//------------------------------------------------------------------------------------
typedef pair<int, int> point;

bool notwall(int numRow, int numCol, int row, int col, vector<string>& grid, vector<vector<int>>& found) {
    return row >= 0 && row < numRow && col >= 0 && col < numCol && !found[row][col] && grid[row][col] != 'W';
}


void reach(int numRow,int numCol, vector<string>& grid, vector<point>& visited, map<point,point>& graph) {
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    point p;
    p.first = 0;
    p.second = 0;
    vector<vector<int>> found(numRow,vector<int>(numCol, false));
    queue<point> que;
    if (grid[p.first][p.second] == '.') {
        que.push(p);
        found[p.first][p.second] = true;
    }

    while (!que.empty()){
        point p1 = que.front();
        que.pop();
        visited.push_back(p1);
        int pfirst = p1.first;
        int psecond = p1.second;
        if (pfirst == numRow-1 && psecond == numCol-1) {
            visited.push_back({numRow-1, numCol-1});
            break;
        }

        for (const auto& dir : directions) {
            int newRow = p1.first + dir.first;
            int newCol = p1.second + dir.second;
            if (notwall(numRow, numCol, newRow, newCol, grid, found)) {
                que.push({newRow, newCol});
                found[newRow][newCol] = true;
                graph[{newRow, newCol}] = p1;
            }
        }
    }
}


void draw(point p1, map<point, point>& graph, int singleSize, int offset1, int offset2) {
    while (graph.count(p1)) {
        DrawRectangle(p1.second * singleSize + offset1, p1.first * singleSize + offset2, singleSize, singleSize, GREEN);
        p1 = graph[p1];
    }
}

//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    int numRow;
    int numCol;
    cin >> numRow >> numCol;
    cin.ignore();

    vector<string> maze;
    for (int j = 0; j < numRow; ++j) {
        string row;
        getline(cin, row);
        maze.push_back(row);
    }

    map<point, point> graph;
    vector<point> visited;
    reach(numRow,numCol, maze, visited, graph);

    size_t m = 0;

    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int singleSize = min( screenWidth / numCol, screenHeight / numRow);
    int offset1 = (screenWidth - singleSize * numCol) / 2;
    int offset2 = (screenHeight - singleSize * numRow) / 2;

    InitWindow(screenWidth, screenWidth, "maze");

    SetTargetFPS(20);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // NOTE: All variables update happens inside GUI control functions
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j ++) {
                if (maze[i][j] == 'W') {
                    DrawRectangle(j * singleSize + offset1, i * singleSize + offset2, singleSize, singleSize, GRAY);
                } else {
                    DrawRectangle(j * singleSize + offset1, i * singleSize + offset2, singleSize, singleSize, WHITE);
                }
            }
        }

        DrawRectangle(offset1, offset2, singleSize, singleSize, GREEN);
        if (m < visited.size()) {
            draw(visited[m], graph, singleSize, offset1, offset2);
            m++;
        } else {
            draw({numRow-1, numCol-1}, graph, singleSize, offset1, offset2);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
