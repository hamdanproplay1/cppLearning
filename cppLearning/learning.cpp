#include <iostream>
#include <Windows.h>
#include <random>
#include <conio.h>

using namespace std;

int snake_y[100] = { 25 };
int snake_x[100] = { 10 };
int randomFoodX;
int randomFoodY;
int snakesize = 1;
char kbInput;

int BOX() {
    int width = 50;
    int height = 20;

    for (int i = 0; i < width + 2; i++) {
        cout << "_";
    }
    cout << "\n";

    for (int i = 0; i < height; i++) {
        cout << "|";

        for (int j = 0; j < width; j++) {
            bool isSnake = false;

            for (int k = 0; k < snakesize; k++) {
                if (snake_x[k] == i && snake_y[k] == j) {
                    isSnake = true;
                    break;
                }
            }

            if (isSnake) {
                cout << "*";
            }
            else if (i == randomFoodY && j == randomFoodX) {
                cout << "@";
            }
            else {
                cout << " ";
            }
        }

        cout << "|";
        cout << "\n";
    }

    for (int i = 0; i < width + 2; i++) {
        cout << "_";
    }
    return 0;
}

void ClearScreen() {
    COORD position;
    position.X = 0;
    position.Y = 0;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        position
    );
}

void afterSnakeEat() {
    randomFoodX = rand() % 50;
    randomFoodY = rand() % 20;
    if (snakesize < 100) {
        snakesize++;
    }
}

void CursorFix() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

int main() {
    srand(time(0));
    afterSnakeEat();

    while (true) {
        ClearScreen();
        CursorFix();
        BOX();

        if (snake_x[0] == randomFoodY && snake_y[0] == randomFoodX) {
            afterSnakeEat();
        }

        
        for (int i = 1; i < snakesize; i++) {
            if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
                ClearScreen();
                cout << "\n\t GAME OVER! You hit your tail!\n";
              
                system("pause");
                return 0; 
            }
        }

        if (_kbhit()) {
            kbInput = _getch();

            
            for (int i = snakesize - 1; i > 0; i--) {
                snake_x[i] = snake_x[i - 1];
                snake_y[i] = snake_y[i - 1];
            }

            
            if (kbInput == 'A' || kbInput == 'a') {
                if (snake_y[0] > 0) {
                    snake_y[0] -= 1;
                }
            }
            if (kbInput == 'D' || kbInput == 'd') {
                if (snake_y[0] < 49) {
                    snake_y[0] += 1;
                }
            }
            if (kbInput == 'S' || kbInput == 's') {
                if (snake_x[0] < 19) {
                    snake_x[0] += 1;
                }
            }
            if (kbInput == 'W' || kbInput == 'w') {
                if (snake_x[0] > 0) {
                    snake_x[0] -= 1;
                }
            }
        }
    }

    return 0;
}