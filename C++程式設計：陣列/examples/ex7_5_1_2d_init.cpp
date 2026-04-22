// ex7_5_1_2d_init.cpp
// 示範二維陣列的宣告與各種初始化方式

#include <iostream>
using namespace std;

int main() {
    // 方式一：完整初始化（推薦，清楚明瞭）
    int a[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    // 方式二：全部初始化為 0
    int c[3][4] = {};

    // 方式三：部分初始化（其餘補 0）
    int d[3][3] = {{1}, {4, 5}, {7, 8, 9}};

    cout << "矩陣 a：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << a[i][j];
            if (j < 3) cout << "\t";
        }
        cout << endl;
    }

    cout << "\n矩陣 d（部分初始化）：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << d[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
