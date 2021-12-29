#include <iostream>
#include <raylib.h>
#include <string>

struct Ball {
    float x, y;
    int r;
    float velX, velY;
};

struct Player {
    Color color;
    float x, y, speed = 500;
    int width = 10, height = 100;
};

int main(int, char**) {
    int screenWidth = 1000;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pong!");

    bool close = 0;
    while (!close) {
        bool scored = 0, ballMove = 0;
        float ballSpeed = 500;
        int p1Score = 0, p2Score = 0;
        Player player1 = { {255, 0, 0, 255}, 0, 250 };
        Player player2 = { {0, 255, 0, 255}, 990, 250 };
        Ball ball = { 492, 292, 8, ballSpeed, -ballSpeed};

        while (!close) {
            if (scored) { ball = { 492, 292, 8, ballSpeed, -ballSpeed}; scored = false; ballMove = 0; }
            if (IsKeyPressed(KEY_SPACE)) ballMove = 1;
            close = WindowShouldClose();
            float frameTime = GetFrameTime();
            bool p1up = 0, p1down = 0;
            if (IsKeyDown(KEY_W) && player1.y > 0) { p1up = true; player1.y -= frameTime*player1.speed; }
            if (IsKeyDown(KEY_S) && player1.y+player1.height < screenHeight) { p1down = true; player1.y += frameTime*player1.speed; }

            bool p2up = 0, p2down = 0;
            if (IsKeyDown(KEY_UP) && player2.y > 0) { p2up = true; player2.y -= frameTime*player2.speed; }
            if (IsKeyDown(KEY_DOWN) && player2.y+player2.height < screenHeight) { p2down = true; player2.y += frameTime*player2.speed; }

            if (ball.velX < 0 && ball.x <= 10 && ball.y + ball.r*2 > player1.y && ball.y < player1.y+player1.height) {
                if (p1up) ball.velY -= 100;
                if (p1down) ball.velY += 100;
                ball.velX = -ball.velX;
                ball.velX *= 1.02;
                ball.velY *= 1.02;
            }

            if (ball.velX > 0 && ball.x+ball.r*2 >= player2.x && ball.y + ball.r*2 > player2.y && ball.y < player2.y+player2.height) {
                if (p2up) ball.velY -= 100;
                if (p2down) ball.velY += 100;
                ball.velX = -ball.velX;
                ball.velX *= 1.02;
                ball.velY *= 1.02;
            }

            if (ball.y < 0 && ball.velY < 0) ball.velY = -ball.velY;
            if (ball.y+ball.r*2 > screenHeight && ball.velY > 0) ball.velY = -ball.velY;
            if (ball.x < 0 && ball.velX < 0) { p2Score++; scored = true; }
            if (ball.x > screenWidth && ball.velX > 0) { p1Score++; scored = true; }

            if (ballMove) {
                ball.x += ball.velX * frameTime;
                ball.y += ball.velY * frameTime;
            }

            BeginDrawing();
                ClearBackground(BLACK);
                int y = 0;
                while (y < screenHeight) {
                    DrawRectangle(screenWidth/2-2, y, 4, 40, WHITE);
                    y+=80;
                }
                DrawRectangle(player1.x, player1.y, player1.width, player1.height, player1.color);
                DrawRectangle(player2.x, player2.y, player2.width, player2.height, player2.color);
                DrawCircle(ball.x+ball.r, ball.y+ball.r, ball.r, { 255, 0, 255, 255 });
                DrawText(std::to_string(p1Score).c_str(), 0, 0, 25, { 255, 0, 0, 255});
                DrawText(std::to_string(p2Score).c_str(), screenWidth-MeasureText(std::to_string(p2Score).c_str(), 25), 0, 25, { 0, 255, 0, 255});
            EndDrawing();
        }
    }
}
