// ex10_4_4_memory_leak.cpp
// 示範：記憶體洩漏 vs 正確釋放（教學對比）
#include <iostream>
using namespace std;

// 正確版本：記得釋放
void good_func(int val) {
    int *p = new int(val);
    cout << "  [正確] 值：" << *p;
    delete p;
    p = nullptr;
    cout << "，已釋放" << endl;
}

// 錯誤版本：記憶體洩漏
void bad_func(int val) {
    int *p = new int(val);
    cout << "  [洩漏] 值：" << *p << "，忘記 delete！" << endl;
    // 沒有 delete p; → 洩漏 4 bytes
}

// 覆蓋指標前忘記釋放
void overwrite_bug() {
    int *p = new int(10);   // 配置 A
    cout << "  p 指向：" << *p << endl;
    p = new int(20);         // 配置 B，但 A 的記憶體洩漏了！
    cout << "  p 改指向：" << *p << endl;
    delete p;                // 只釋放 B，A 永遠洩漏
}

// 正確版本：覆蓋前先釋放
void overwrite_correct() {
    int *p = new int(10);
    cout << "  p 指向：" << *p << endl;
    delete p;                // 先釋放舊的
    p = new int(20);
    cout << "  p 改指向：" << *p << endl;
    delete p;
    p = nullptr;
}

int main() {
    cout << "=== 正確釋放 ===" << endl;
    for (int i = 1; i <= 3; i++) good_func(i * 10);

    cout << "\n=== 記憶體洩漏（請勿模仿）===" << endl;
    for (int i = 1; i <= 3; i++) bad_func(i * 10);
    cout << "  共洩漏 " << 3 * sizeof(int) << " bytes" << endl;

    cout << "\n=== 覆蓋指標前忘記釋放（錯誤）===" << endl;
    overwrite_bug();

    cout << "\n=== 覆蓋指標正確做法 ===" << endl;
    overwrite_correct();

    return 0;
}
