#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>
#endif

using namespace std;

const int width = 10;
const int height = 20;

int board[height][width] = {0};
int currentPiece[4][4];
int pieceX, pieceY;
int score = 0;
bool gameOver = false;
int fallTimer = 0;

// Simple 3D array for the 7 classic shapes
int shapes[7][4][4] = {
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // I
    {{0,0,0,0}, {0,2,2,0}, {0,2,2,0}, {0,0,0,0}}, // O
    {{0,0,0,0}, {0,3,0,0}, {3,3,3,0}, {0,0,0,0}}, // T
    {{0,0,0,0}, {0,4,4,0}, {4,4,0,0}, {0,0,0,0}}, // S
    {{0,0,0,0}, {5,5,0,0}, {0,5,5,0}, {0,0,0,0}}, // Z
    {{0,0,0,0}, {6,0,0,0}, {6,6,6,0}, {0,0,0,0}}, // J
    {{0,0,0,0}, {0,0,7,0}, {7,7,7,0}, {0,0,0,0}}  // L
};

void SpawnPiece() {
    int type = rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentPiece[i][j] = shapes[type][i][j];
        }
    }
    pieceX = width / 2 - 2;
    pieceY = 0;
}

bool CheckCollision(int nextX, int nextY, int tempPiece[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tempPiece[i][j] != 0) {
                int boardX = nextX + j;
                int boardY = nextY + i;

                if (boardX < 0 || boardX >= width || boardY >= height) 
                    return true;
                if (boardY >= 0 && board[boardY][boardX] != 0) 
                    return true;
            }
        }
    }
    return false;
}

void Rotate() {
    int rotated[4][4] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotated[j][3 - i] = currentPiece[i][j];
        }
    }
    if (!CheckCollision(pieceX, pieceY, rotated)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentPiece[i][j] = rotated[i][j];
            }
        }
    }
}

void LockPiece() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece[i][j] != 0 && pieceY + i >= 0) {
                board[pieceY + i][pieceX + j] = currentPiece[i][j];
            }
        }
    }

    // Line Clear Check
    for (int i = height - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < width; j++) {
            if (board[i][j] == 0) full = false;
        }
        if (full) {
            score += 100;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < width; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 0; j < width; j++) board[0][j] = 0;
            i++; // Re-check same row index
        }
    }

    SpawnPiece();
    if (CheckCollision(pieceX, pieceY, currentPiece)) {
        gameOver = true;
    }
}

void Draw() {
#ifdef _WIN32
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
#else
    cout << "\033[H";
#endif

    // Top border
    for (int i = 0; i < width + 2; i++) cout << "##";
    cout << endl;

    for (int i = 0; i < height; i++) {
        cout << "##"; // Left border
        for (int j = 0; j < width; j++) {
            // Determine if a falling piece block is here
            int blockType = board[i][j];
            if (i >= pieceY && i < pieceY + 4 && j >= pieceX && j < pieceX + 4) {
                if (currentPiece[i - pieceY][j - pieceX] != 0) {
                    blockType = currentPiece[i - pieceY][j - pieceX];
                }
            }

            // Draw based on type
            if (blockType == 0) cout << "  ";
            else cout << "[]"; 
        }
        cout << "##" << endl; // Right border
    }

    // Bottom border
    for (int i = 0; i < width + 2; i++) cout << "##";
    cout << endl;

    cout << "Score: " << score << "      " << endl;
    cout << "Controls: A/D = Left/Right, W = Rotate, S = Soft Drop, Esc = Quit" << endl;
}

void Input() {
#ifdef _WIN32
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (!CheckCollision(pieceX - 1, pieceY, currentPiece)) pieceX--; break;
            case 'd': if (!CheckCollision(pieceX + 1, pieceY, currentPiece)) pieceX++; break;
            case 'w': Rotate(); break;
            case 's': if (!CheckCollision(pieceX, pieceY + 1, currentPiece)) pieceY++; break;
            case 27:  gameOver = true; break;
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    struct timeval tv = {0, 0};

    if (select(1, &rfds, NULL, NULL, &tv) > 0) {
        char ch = getchar();
        switch (ch) {
            case 'a': if (!CheckCollision(pieceX - 1, pieceY, currentPiece)) pieceX--; break;
            case 'd': if (!CheckCollision(pieceX + 1, pieceY, currentPiece)) pieceX++; break;
            case 'w': Rotate(); break;
            case 's': if (!CheckCollision(pieceX, pieceY + 1, currentPiece)) pieceY++; break;
            case 27:  gameOver = true; break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

void Logic() {
    fallTimer++;
    if (fallTimer >= 15) { // Downward gravity speed
        fallTimer = 0;
        if (!CheckCollision(pieceX, pieceY + 1, currentPiece)) {
            pieceY++;
        } else {
            LockPiece();
        }
    }
}

int main() {
    srand(time(nullptr));
    
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J";
#endif

    SpawnPiece();

    while (!gameOver) {
        Draw();
        Input();
        Logic();

#ifdef _WIN32
        Sleep(30);
#else
        usleep(30000);
#endif
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}