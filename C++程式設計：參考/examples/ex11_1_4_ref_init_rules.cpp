#include <iostream>
using namespace std;

int main() {
    // ✅ 合法：初始化時綁定可修改的左值
    int a = 10;
    int& r1 = a;
    cout << "r1 = " << r1 << endl;

    // ✅ 合法：多個參考可以指向同一變數
    int& r2 = a;
    int& r3 = r1;    // r3 是 a 的別名（不是 r1 的別名）
    r2 = 99;
    cout << "a=" << a << " r1=" << r1 << " r2=" << r2 << " r3=" << r3 << endl;

    // ✅ 合法：const 參考可以綁定字面值
    const int& cr1 = 42;
    cout << "cr1 = " << cr1 << endl;

    // ✅ 合法：const 參考可以綁定臨時運算式
    const int& cr2 = a * 2 + 1;
    cout << "cr2 = a*2+1 = " << cr2 << endl;

    // ✅ 合法：參考可以在宣告的同時修改
    int b = 5;
    int& r4 = b;
    r4 += 10;
    cout << "b 透過 r4 加 10 後：b = " << b << endl;

    // ❌ 以下為非法（已用註解展示，取消後編譯器會報錯）：

    // int& r5;               // 錯誤：參考必須初始化
    // int& r6 = 42;          // 錯誤：非 const 參考不能綁定字面值
    // int& r7 = a + 1;       // 錯誤：非 const 參考不能綁定臨時值
    // int& r8 = nullptr;     // 錯誤：參考不能是 null

    cout << "\n=== 規則摘要 ===" << endl;
    cout << "1. 參考必須在宣告時初始化" << endl;
    cout << "2. 一旦綁定，無法重新指向其他變數" << endl;
    cout << "3. 非 const 參考只能綁定可修改的左值" << endl;
    cout << "4. const 參考可以綁定左值、字面值、臨時值" << endl;
    cout << "5. 多個參考可以指向同一變數" << endl;

    return 0;
}
