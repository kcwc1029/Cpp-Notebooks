// ex10_1_3_nullptr_safety.cpp
// 示範：nullptr 空指標的安全使用
#include <iostream>
using namespace std;

void safe_use(int *p) {
    if (p == nullptr) {
        cout << "警告：收到空指標，略過操作" << endl;
        return;
    }
    cout << "安全使用，值為：" << *p << endl;
    *p *= 2;
}

int main() {
    // 未初始化的指標很危險，永遠初始化為 nullptr
    int *p = nullptr;
    cout << "p 的值：" << p << endl;

    // 使用前先檢查
    if (p == nullptr) {
        cout << "p 是空指標，不能解參考" << endl;
    }

    int x = 99;
    p = &x;   // 現在 p 指向有效的變數

    if (p != nullptr) {
        cout << "p 指向的值：" << *p << endl;
    }

    safe_use(nullptr);   // 安全：函式內會檢查
    safe_use(p);         // 正常使用
    cout << "x 被修改為：" << x << endl;

    p = nullptr;         // 用完設回 nullptr（良好習慣）
    cout << "重設後 p = " << p << endl;

    return 0;
}
