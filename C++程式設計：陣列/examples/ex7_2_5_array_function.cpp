// ex7_2_5_array_function.cpp
// 示範陣列傳入函式：const 保護、傳址修改、額外傳入大小

#include <iostream>
using namespace std;

// 只讀：加 const 防止函式意外修改陣列
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl;
}

// 計算總和（只讀）
int sum(const int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) total += arr[i];
    return total;
}

// 修改陣列（傳址語意，影響原始陣列）
void fillZero(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = 0;
}

int main() {
    int scores[5] = {85, 92, 78, 95, 88};

    cout << "原始：";
    printArray(scores, 5);

    cout << "總和：" << sum(scores, 5) << endl;
    cout << "平均：" << sum(scores, 5) / 5.0 << endl;

    fillZero(scores, 5);
    cout << "清零後：";
    printArray(scores, 5);

    return 0;
}
