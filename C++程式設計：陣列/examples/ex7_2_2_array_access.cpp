// ex7_2_2_array_access.cpp
// 示範陣列元素的讀取、修改與迴圈存取

#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // 讀取
    cout << "第一個元素：" << arr[0] << endl;   // 10
    cout << "最後一個：" << arr[4] << endl;      // 50

    // 修改
    arr[2] = 99;
    cout << "修改後 arr[2]：" << arr[2] << endl; // 99

    // 用迴圈讀取所有元素
    cout << "全部元素：";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 用迴圈輸入
    int scores[5];
    cout << "\n請輸入 5 個成績：";
    for (int i = 0; i < 5; i++) {
        cin >> scores[i];
    }

    cout << "你輸入的成績：";
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    return 0;
}
