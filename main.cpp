#include "raylib.h"
#include <iostream>

//Types and struct definitions
int CpuScore = 0;
int PlayerScore = 0;
class Paddle {
public:
    int speed;
    int x;
    int y;
    int height;
    int width;

    void DrawPaddle() {
        DrawRectangle(x, y, width, height, RAYWHITE);
    }
    void UpdatePaddle() {
        if (IsKeyDown(KEY_DOWN) && y + height <= GetScreenHeight()) {
            y += speed;
        }
        if (IsKeyDown(KEY_UP) && y >= 0) {
            y -= speed;
        }
    }
} ;
Paddle leftPaddle;


class CpuPaddle : public Paddle {
public:
    void Update(int ball_y) {
        if (y + height/2 > ball_y) {
            y = y - speed;
        }
        if (y + height/2 <= ball_y) {
            y = y + speed;
        }
    }
} ;
CpuPaddle CpuPad;
class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;
    void DrawBall() {
        DrawCircle(x, y, radius, RAYWHITE);
    }
    void ResetBall() {
        x= GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speed_Choices[2] = {-1, 1};
        speed_x *= speed_Choices[GetRandomValue(0, 1)];
        speed_y *= speed_Choices[GetRandomValue(0, 1)];
    }
    void UpdateBall() {
        if ( (y + radius) >= GetScreenHeight() || (y-radius) <= 0) {
            speed_y *= -1;
        }
        if ( (x + radius) >= GetScreenWidth()) {
            ResetBall();
            PlayerScore ++ ;

        }
        if ((x-radius) <= 0  ) {
            ResetBall();
            CpuScore ++ ;

        }

        // bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
        if (CheckCollisionCircleRec((Vector2){x, y}, radius, (Rectangle){(float)leftPaddle.x, (float)leftPaddle.y, (float)leftPaddle.width, (float)leftPaddle.height})) {
            x = leftPaddle.x + leftPaddle.width + radius;
            speed_x *= -1;
        }
        if (CheckCollisionCircleRec((Vector2){x, y}, radius, (Rectangle){(float)CpuPad.x, (float)CpuPad.y, (float)CpuPad.width, (float)CpuPad.height})) {
            x = CpuPad.x - radius;
            speed_x *= -1;
        }


    x  += speed_x; y  += speed_y;


    }
} ;
    Ball ball;
    int main() {
        const int screenWidth = 1200;
        const int screenHeight = 800;
        ball.x = screenWidth / 2;
        ball.y = screenHeight / 2;
        ball.speed_x = 7;
        ball.speed_y = 7;
        ball.radius = 30;

        leftPaddle.x = 15;
        leftPaddle.width = 30;
        leftPaddle.height = 120;
        leftPaddle.y = screenHeight / 2 - 60;
        leftPaddle.speed = 7;

        CpuPad.x = screenWidth - (15+30);
        CpuPad.y = screenHeight / 2 - 60;
        CpuPad.height = 120;
        CpuPad.width = 30;
        CpuPad.speed = 6;

        InitWindow(screenWidth, screenHeight, "Ping Pong");
        SetTargetFPS(60);
        //Main game loop
        while (!WindowShouldClose()) {


            BeginDrawing();

            leftPaddle.UpdatePaddle();
            ball.UpdateBall();
            CpuPad.Update(ball.y);
            ClearBackground(BLACK); // Clears background every frame with black and then draws the follwoing every frame
            ball.DrawBall(); //DrawRectangle(15, screenHeight / 2 - 60, 30, 120, RAYWHITE);
            leftPaddle.DrawPaddle();
            CpuPad.DrawPaddle();
            DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, RAYWHITE);
            DrawText(TextFormat("%i",PlayerScore), screenWidth/4-20, 20, 80 , WHITE);
            DrawText(TextFormat("%i",CpuScore), 3*screenWidth/4-20, 20, 80 , WHITE);
            EndDrawing(); // No more drawing after this
        }

        CloseWindow(); // Closes window when while loop finishes
        return 0;
    }
