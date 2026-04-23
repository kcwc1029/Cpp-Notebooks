// ex10_5_1_pointer_pitfalls.cpp
// 示範：指標常見陷阱的安全處理方式
#include <iostream>
using namespace std;

int main() {
    cout << "=== 良好的指標生命週期管理 ===" << endl;

    // 1. 永遠初始化指標
    int *p = nullptr;
    cout << "初始化為 nullptr：p = " << p << endl;

    // 2. 使用前檢查
    if (p == nullptr) {
        p = new int(42);
        cout << "配置後：*p = " << *p << endl;
    }

    // 3. 使用完畢後釋放並設 nullptr
    delete p;
    p = nullptr;
    cout << "釋放後：p = " << (p ? "非空" : "nullptr") << endl;

    // 4. delete nullptr 是安全的（double-free 防護）
    delete p;   // 不會崩潰
    cout << "再次 delete nullptr：安全" << endl;

    cout << "\n=== 動態陣列安全管理 ===" << endl;
    int n = 5;
    int *arr = new int[n]{1, 2, 3, 4, 5};
    cout << "陣列：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    delete[] arr;    // 注意：要用 delete[]
    arr = nullptr;
    cout << "delete[] 後：arr = " << (arr ? "非空" : "nullptr") << endl;

    cout << "\n=== 避免回傳區域變數指標 ===" << endl;
    // 正確：使用靜態變數
    auto safe_return = []() -> int* {
        static int x = 100;
        return &x;
    };
    int *sp = safe_return();
    cout << "靜態變數指標：*sp = " << *sp << endl;

    cout << "\n=== 指標使用前後比較 ===" << endl;
    cout << "原則：init→check→use→delete→nullptr" << endl;

    return 0;
}
