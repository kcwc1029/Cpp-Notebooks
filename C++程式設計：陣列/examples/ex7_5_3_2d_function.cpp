// ex7_5_3_2d_function.cpp
// 示範二維陣列傳入函式（行數必須固定）

#include <iostream>
#include <iomanip>
using namespace std;

const int COLS = 4;

void printMatrix(const int arr[][COLS], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) cout << setw(5) << arr[i][j];
        cout << endl;
    }
}

int sumAll(const int arr[][COLS], int rows) {
    int total = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < COLS; j++)
            total += arr[i][j];
    return total;
}

int main() {
    int matrix[3][COLS] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    cout << "矩陣：" << endl;
    printMatrix(matrix, 3);

    cout << "\n所有元素總和：" << sumAll(matrix, 3) << endl;

    return 0;
}
