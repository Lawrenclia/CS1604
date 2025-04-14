#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <cmath>

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "YingYangMap");

    float centerX = (GetScreenWidth() - 300)/2.0f;  //确定图片中心
    float centerY = (GetScreenWidth() - 300)/2.0f;  //确定图片中心，too.
    Vector2 center = {centerX, centerY};

    float angle = 0.0f;
    int segment = 100;

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(RAYWHITE);   //清空背景
            DrawCircle(centerX, centerY, 120, WHITE);  //绘出白色大圆
            DrawCircleLines(centerX, centerY, 120, BLACK);  //绘出黑色边框
            DrawCircleSector(center, 120, angle, angle + 180.0f, segment, BLACK); //绘出黑色半圆
            DrawCircle(centerX - 60*cos(angle * M_PI / 180), centerY - 60*sin(angle * M_PI / 180), 60, WHITE); //绘出能移动的白色圆
            DrawCircle(centerX - 60*cos(angle * M_PI / 180 + M_PI), centerY - 60*sin(angle * M_PI / 180 + M_PI), 60, BLACK); //绘出能移动的黑色圆
            DrawCircle(centerX - 60*cos(angle * M_PI / 180), centerY - 60*sin(angle * M_PI / 180), 10, BLACK); //绘出能移动的黑色小圆
            DrawCircle(centerX - 60*cos(angle * M_PI / 180 + M_PI), centerY - 60*sin(angle * M_PI / 180 + M_PI), 10, WHITE); //绘出能移动的白色小圆

            GuiSliderBar((Rectangle){ 500, 200, 200, 30}, "Angle", TextFormat("%.2f", angle), &angle, 0, 720); //设置控制条

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
