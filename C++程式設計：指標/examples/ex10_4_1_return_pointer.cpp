// ex10_4_1_return_pointer.cpp
// 示範：安全地從函式回傳指標
#include <iostream>
using namespace std;

// 正確：回傳靜態變數的指標（static 不隨函式消失）
int* get_counter() {
    static int count = 0;
    count++;
    return &count;
}

// 正確：回傳陣列中最大值的指標
int* find_max(int *arr, int n) {
    int *max_p = arr;
    for (int i = 1; i < n; i++) {
        if (arr[i] > *max_p) max_p = &arr[i];
    }
    return max_p;
}

// 正確：回傳陣列中第一個符合條件的元素指標
int* find_first(int *arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return &arr[i];
    }
    return nullptr;   // 找不到時回傳 nullptr
}

int main() {
    cout << "=== 靜態計數器 ===" << endl;
    int *c = get_counter();
    cout << "計數：" << *c << endl;
    get_counter();
    get_counter();
    cout << "計數：" << *c << endl;   // 靜態變數，指標仍有效

    cout << "\n=== 找最大值並修改 ===" << endl;
    int scores[] = {78, 92, 55, 88, 100, 63};
    int *top = find_max(scores, 6);
    cout << "最高分位於索引：" << (top - scores) << "，值：" << *top << endl;
    *top = 0;   // 清除最高分
    cout << "清除後：";
    for (int i = 0; i < 6; i++) cout << scores[i] << " ";
    cout << endl;

    cout << "\n=== 搜尋特定值 ===" << endl;
    int *pos = find_first(scores, 6, 88);
    if (pos != nullptr) {
        cout << "找到 88，索引：" << (pos - scores) << endl;
        *pos = 88 + 10;   // 加 10 分
    }
    for (int i = 0; i < 6; i++) cout << scores[i] << " ";
    cout << endl;

    pos = find_first(scores, 6, 999);
    if (pos == nullptr) cout << "找不到 999" << endl;

    return 0;
}
