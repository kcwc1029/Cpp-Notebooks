// ex7_1_1_array_intro.cpp
// 示範陣列的基本概念：與一般變數的比較、連續記憶體驗證

#include <iostream>
using namespace std;

int main() {
    // 一般變數：5 個分開的變數，無法用迴圈處理
    int s0 = 85, s1 = 92, s2 = 78, s3 = 95, s4 = 88;

    // 陣列：5 個元素存在連續記憶體，可用迴圈操作
    int score[5] = {85, 92, 78, 95, 88};

    // 用迴圈計算平均（一般變數做不到）
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += score[i];
    }
    cout << "平均：" << sum / 5.0 << endl;

    // 顯示各元素的記憶體位址（驗證連續性）
    cout << "\n各元素記憶體位址：" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "score[" << i << "] 位址：" << &score[i] << endl;
    }
    // 每個位址差 4 bytes（int 大小）

    return 0;
}
