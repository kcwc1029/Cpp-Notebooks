// ex7_5_2_2d_traverse.cpp
// 示範二維陣列遍歷：每列總和、每行總和、對角線

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int rows = 3, cols = 4;
    int matrix[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    cout << "矩陣：" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cout << setw(4) << matrix[i][j];
        cout << endl;
    }

    // 每列總和
    cout << "\n每列總和：" << endl;
    for (int i = 0; i < rows; i++) {
        int rowSum = 0;
        for (int j = 0; j < cols; j++) rowSum += matrix[i][j];
        cout << "第 " << i << " 列：" << rowSum << endl;
    }

    // 每行總和
    cout << "\n每行總和：" << endl;
    for (int j = 0; j < cols; j++) {
        int colSum = 0;
        for (int i = 0; i < rows; i++) colSum += matrix[i][j];
        cout << "第 " << j << " 行：" << colSum << endl;
    }

    // 方陣對角線
    int sq[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int diagSum = 0;
    for (int i = 0; i < 3; i++) diagSum += sq[i][i];
    cout << "\n對角線總和（1+5+9）：" << diagSum << endl;

    return 0;
}
