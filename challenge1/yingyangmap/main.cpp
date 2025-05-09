#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <cmath>

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "YingYangMap");

    float centerX = (GetScreenWidth() - 300)/2.0f;  //ȷ��ͼƬ����
    float centerY = (GetScreenWidth() - 300)/2.0f;  //ȷ��ͼƬ���ģ�too.
    Vector2 center = {centerX, centerY};

    float angle = 0.0f;
    int segment = 100;

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(RAYWHITE);   //��ձ���
            DrawCircle(centerX, centerY, 120, WHITE);  //�����ɫ��Բ
            DrawCircleLines(centerX, centerY, 120, BLACK);  //�����ɫ�߿�
            DrawCircleSector(center, 120, angle, angle + 180.0f, segment, BLACK); //�����ɫ��Բ
            DrawCircle(centerX - 60*cos(angle * M_PI / 180), centerY - 60*sin(angle * M_PI / 180), 60, WHITE); //������ƶ��İ�ɫԲ
            DrawCircle(centerX - 60*cos(angle * M_PI / 180 + M_PI), centerY - 60*sin(angle * M_PI / 180 + M_PI), 60, BLACK); //������ƶ��ĺ�ɫԲ
            DrawCircle(centerX - 60*cos(angle * M_PI / 180), centerY - 60*sin(angle * M_PI / 180), 10, BLACK); //������ƶ��ĺ�ɫСԲ
            DrawCircle(centerX - 60*cos(angle * M_PI / 180 + M_PI), centerY - 60*sin(angle * M_PI / 180 + M_PI), 10, WHITE); //������ƶ��İ�ɫСԲ

            GuiSliderBar((Rectangle){ 500, 200, 200, 30}, "Angle", TextFormat("%.2f", angle), &angle, 0, 720); //���ÿ�����

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
