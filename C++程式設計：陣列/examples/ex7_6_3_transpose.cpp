// ex7_6_3_transpose.cpp
// 矩陣轉置：B[j][i] = A[i][j]（列行互換）

#include <iostream>
#include <iomanip>
using namespace std;

const int ROWS = 3, COLS = 4;

void transpose(const int A[][COLS], int B[][ROWS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            B[j][i] = A[i][j];
}

int main() {
    int A[ROWS][COLS] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
    int B[COLS][ROWS] = {};
    transpose(A, B);

    cout << "原矩陣 A（3×4）：" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) cout << setw(5) << A[i][j];
        cout << endl;
    }

    cout << "\n轉置後 B（4×3）：" << endl;
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) cout << setw(5) << B[i][j];
        cout << endl;
    }

    return 0;
}
