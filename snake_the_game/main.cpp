#include <iostream>

#include <windows.h>

#include <conio.h>

using namespace std;

const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 20;
bool gameOver;
int x, y, score, fruit_x, fruit_y;
enum Direction {
    IDLE, UP, DOWN, LEFT, RIGHT
} direction;

void Setup() {
    x = FIELD_WIDTH / 2;
    y = FIELD_HEIGHT / 2;
    fruit_x = rand() % FIELD_WIDTH;
    fruit_y = rand() % FIELD_HEIGHT;
    score = 0;
    gameOver = false;
    direction = IDLE;
}

void Draw() {
    for (int i = 0; i < FIELD_WIDTH + 1; ++i) {
        cout << '#';
    }
    cout << endl;
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (j == 0 || j == FIELD_WIDTH - 1) {
                cout << '#';
            }
            if (i == y && x == j) {
                cout << 'O';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
    for (int i = 0; i < FIELD_WIDTH + 1; ++i) {
        cout << '#';
    }
    cout << endl;
}

void Logic() {
    switch (direction) {
        case LEFT:
            --x;
            break;
        case RIGHT:
            ++x;
            break;
        case UP:
            ++y;
            break;
        case DOWN:
            --y;
            break;
        default:
            break;
    }
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                direction = LEFT;
                break;
            case 'd':
                direction = RIGHT;
                break;
            case 's':
                direction = DOWN;
                break;
            case 'w':
                direction = UP;
                break;
            case 'z':
                gameOver = true;
                break;
        }
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }
    return 0;
}