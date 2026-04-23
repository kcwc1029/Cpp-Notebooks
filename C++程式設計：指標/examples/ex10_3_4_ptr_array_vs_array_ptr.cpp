// ex10_3_4_ptr_array_vs_array_ptr.cpp
// 示範：指標陣列 vs 陣列指標（容易混淆的概念）
#include <iostream>
using namespace std;

int main() {
    int a = 1, b = 2, c = 3, d = 4;

    cout << "=== 指標陣列：int *ptr_arr[4] ===" << endl;
    // 這是一個陣列，每個元素都是 int*
    int *ptr_arr[4] = {&a, &b, &c, &d};
    cout << "四個指標各自指向：";
    for (int i = 0; i < 4; i++) {
        cout << *ptr_arr[i] << " ";
    }
    cout << endl;

    *ptr_arr[1] = 99;   // 透過指標陣列修改 b
    cout << "b 被改為：" << b << endl;

    cout << "\n=== 陣列指標：int (*p)[4] ===" << endl;
    // 這是一個指標，指向含 4 個 int 的整個陣列
    int row0[] = {10, 20, 30, 40};
    int row1[] = {50, 60, 70, 80};

    int (*arr_ptr)[4] = &row0;   // 指向 row0 這個陣列
    cout << "arr_ptr 指向 row0：";
    for (int i = 0; i < 4; i++) cout << (*arr_ptr)[i] << " ";
    cout << endl;

    arr_ptr = &row1;             // 改指向 row1
    cout << "arr_ptr 改指向 row1：";
    for (int i = 0; i < 4; i++) cout << (*arr_ptr)[i] << " ";
    cout << endl;

    cout << "\n=== 二維陣列 + 陣列指標 ===" << endl;
    int matrix[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    int (*row)[4] = matrix;   // row 指向第一列

    for (int i = 0; i < 3; i++) {
        cout << "第 " << i << " 列：";
        for (int j = 0; j < 4; j++) cout << row[i][j] << "\t";
        cout << endl;
    }

    return 0;
}
