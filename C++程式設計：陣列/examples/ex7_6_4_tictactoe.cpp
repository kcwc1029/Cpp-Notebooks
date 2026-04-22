// ex7_6_4_tictactoe.cpp
// 井字遊戲（Tic-Tac-Toe）：用 3×3 二維陣列實作棋盤

#include <iostream>
using namespace std;

int board[3][3] = {};   // 0=空, 1=X, 2=O

void printBoard() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            if      (board[i][j] == 0) cout << ".";
            else if (board[i][j] == 1) cout << "X";
            else                       cout << "O";
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "  ─────" << endl;
    }
}

bool checkWin(int player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0]==player && board[i][1]==player && board[i][2]==player) return true;
        if (board[0][i]==player && board[1][i]==player && board[2][i]==player) return true;
    }
    if (board[0][0]==player && board[1][1]==player && board[2][2]==player) return true;
    if (board[0][2]==player && board[1][1]==player && board[2][0]==player) return true;
    return false;
}

bool isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0) return false;
    return true;
}

int main() {
    cout << "=== 井字遊戲 ===" << endl;
    cout << "玩家1=X，玩家2=O，輸入格式：列 行" << endl << endl;

    int cur = 1;
    while (true) {
        printBoard();
        cout << "\n玩家 " << cur << " (" << (cur==1?"X":"O") << ") 請走棋：";
        int row, col;
        cin >> row >> col;

        if (row<0||row>2||col<0||col>2) { cout << "超出範圍！\n"; continue; }
        if (board[row][col] != 0)        { cout << "位置已佔！\n"; continue; }

        board[row][col] = cur;

        if (checkWin(cur)) { printBoard(); cout << "\n玩家 " << cur << " 獲勝！\n"; break; }
        if (isFull())      { printBoard(); cout << "\n平局！\n"; break; }

        cur = (cur == 1) ? 2 : 1;
    }

    return 0;
}
