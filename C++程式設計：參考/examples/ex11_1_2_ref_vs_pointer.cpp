#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;

    // === 指標操作 ===
    cout << "=== 指標 ===" << endl;
    int* p = &x;
    cout << "p 指向 x，*p = " << *p << endl;

    p = &y;           // 指標可以改變指向
    cout << "p 改指向 y，*p = " << *p << endl;

    *p = 99;          // 透過指標修改 y
    cout << "修改後 y = " << y << endl;

    // === 參考操作 ===
    cout << "\n=== 參考 ===" << endl;
    int& r = x;       // 必須立即初始化
    cout << "r 是 x 的別名，r = " << r << endl;

    // r = &y;        // ❌ 這樣寫是錯誤的！
    r = y;            // 這是「把 y 的值存入 x」，不是改變綁定
    cout << "r = y 後：x = " << x << "，r 還是 x 的別名" << endl;
    cout << "&r == &x：" << (&r == &x ? "true" : "false") << endl;

    // === 使用便利性比較 ===
    cout << "\n=== 使用便利性 ===" << endl;
    int val = 42;
    int* ptr = &val;
    int& ref = val;

    // 指標需要解參考運算子 *
    *ptr += 10;
    cout << "指標：*ptr += 10 → val = " << val << endl;

    // 參考直接使用，像普通變數
    ref += 10;
    cout << "參考：ref += 10  → val = " << val << endl;

    // === 不能用指標做的事，參考也不行 ===
    cout << "\n=== 差異比較 ===" << endl;
    cout << "指標可以是 nullptr：int* p2 = nullptr;  → 合法" << endl;
    cout << "參考不能是 null  ：（無 null 參考概念）" << endl;
    cout << "指標可以算術：ptr + 1  → 移動到下一個位址" << endl;
    cout << "參考沒有算術：ref 就是 val 本身" << endl;

    return 0;
}
