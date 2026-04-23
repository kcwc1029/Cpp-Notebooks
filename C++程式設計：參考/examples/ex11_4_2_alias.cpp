#include <iostream>
using namespace std;

int main() {
    // === 場景 1：簡化矩陣元素存取 ===
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "=== 別名簡化矩陣存取 ===" << endl;

    // 不用別名：每次都要寫 matrix[1][1]
    cout << "中心元素（前）：" << matrix[1][1] << endl;

    // 用別名：清晰且高效（不複製，直接存取）
    int& center = matrix[1][1];
    center = 99;
    cout << "中心元素（後）：" << center << endl;
    cout << "matrix[1][1] = " << matrix[1][1] << endl;    // 同步改變

    // === 場景 2：用別名遍歷並操作每行的首尾 ===
    cout << "\n=== 每行首尾交換 ===" << endl;
    int data[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };

    cout << "處理前：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cout << data[i][j] << "\t";
        cout << endl;
    }

    for (int i = 0; i < 3; i++) {
        int& first = data[i][0];    // 每行第一個元素的別名
        int& last  = data[i][2];    // 每行最後元素的別名
        // 交換首尾
        int temp = first;
        first = last;
        last  = temp;
    }

    cout << "首尾交換後：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cout << data[i][j] << "\t";
        cout << endl;
    }

    // === 場景 3：別名讓複雜條件更清晰 ===
    cout << "\n=== 別名簡化條件判斷 ===" << endl;
    int arr[5] = {3, 7, 1, 9, 5};
    int maxIdx = 0;
    for (int i = 1; i < 5; i++) {
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    }

    // 用別名直接操作最大值，比 arr[maxIdx] 更可讀
    int& maxVal = arr[maxIdx];
    cout << "最大值 = " << maxVal << "（在索引 " << maxIdx << "）" << endl;
    maxVal *= 10;    // 比 arr[maxIdx] *= 10 更直覺
    cout << "乘以 10 後：";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
