#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
vector<vector<int>> board(HEIGHT, vector<int>(WIDTH, 0));

// 블록 모양 (회전 포함)
vector<vector<vector<int>>> tetromino = {
    {{1, 1, 1, 1}},                    // I
    {{1, 1}, {1, 1}},                  // O
    {{0, 1, 0}, {1, 1, 1}},            // T
    {{1, 0, 0}, {1, 1, 1}},            // L
    {{0, 0, 1}, {1, 1, 1}}             // J
};

int current = 0;
int x = WIDTH / 2 - 1;
int y = 0;
bool gameOver = false;

void gotoxy(int a, int b) {
    COORD pos = { (SHORT)a, (SHORT)b };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawBoard() {
    gotoxy(0, 0);
    cout << "←/→ 이동 | ↓ 빠르게 내리기 | Space 회전 | ESC 종료\n";
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == 1)
                cout << "[]";
            else
                cout << "· ";
        }
        cout << endl;
    }
}

bool isValidPosition(int nx, int ny, vector<vector<int>>& shape) {
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j]) {
                int newX = nx + j;
                int newY = ny + i;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT) return false;
                if (newY >= 0 && board[newY][newX]) return false;
            }
        }
    }
    return true;
}

void mergeBlock(vector<vector<int>>& shape) {
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j]) board[y + i][x + j] = 1;
        }
    }
}

void rotateBlock(vector<vector<int>>& shape) {
    int n = shape.size(), m = shape[0].size();
    vector<vector<int>> rotated(m, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            rotated[j][n - 1 - i] = shape[i][j];
    shape = rotated;
}

void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < WIDTH; j++) {
            if (!board[i][j]) { full = false; break; }
        }
        if (full) {
            for (int k = i; k > 0; k--) {
                board[k] = board[k - 1];
            }
            board[0] = vector<int>(WIDTH, 0);
            i++;
        }
    }
}

int main() {
    system("cls");
    srand(time(NULL));
    vector<vector<int>> shape = tetromino[current];

    while (!gameOver) {
        // 키 입력 처리
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (isValidPosition(x - 1, y, shape)) x--;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (isValidPosition(x + 1, y, shape)) x++;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (isValidPosition(x, y + 1, shape)) y++;
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            auto temp = shape;
            rotateBlock(temp);
            if (isValidPosition(x, y, temp)) shape = temp;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            gameOver = true;
            break;
        }

        // 중력
        if (isValidPosition(x, y + 1, shape)) y++;
        else {
            mergeBlock(shape);
            clearLines();
            current = rand() % tetromino.size();
            shape = tetromino[current];
            x = WIDTH / 2 - 1;
            y = 0;
            if (!isValidPosition(x, y, shape)) gameOver = true;
        }

        // 보드 출력
        drawBoard();

        // 현재 블록 그리기
        for (int i = 0; i < shape.size(); i++) {
            for (int j = 0; j < shape[i].size(); j++) {
                if (shape[i][j]) {
                    gotoxy((x + j) * 2, y + i + 1); // +1은 안내문 아래줄부터
                    cout << "[]";
                }
            }
        }

        Sleep(200);
    }

    gotoxy(0, HEIGHT + 2);
    cout << "!! GAME OVER !!\n";
    return 0;
}