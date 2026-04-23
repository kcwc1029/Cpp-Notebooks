// ex10_2_1_pass_by_ptr.cpp
// 示範：傳值 vs 傳指標的行為差異
#include <iostream>
using namespace std;

void add_ten_value(int x) {
    x += 10;
    cout << "  [傳值] 函式內 x = " << x << endl;
}

void add_ten_ptr(int *p) {
    *p += 10;
    cout << "  [傳指標] 函式內 *p = " << *p << endl;
}

void set_to_zero(double *p) {
    *p = 0.0;
}

int main() {
    int a = 5, b = 5;

    cout << "=== 傳值（不影響原始變數）===" << endl;
    cout << "呼叫前 a = " << a << endl;
    add_ten_value(a);
    cout << "呼叫後 a = " << a << endl;   // 仍是 5

    cout << "\n=== 傳指標（真正修改原始變數）===" << endl;
    cout << "呼叫前 b = " << b << endl;
    add_ten_ptr(&b);
    cout << "呼叫後 b = " << b << endl;   // 變成 15

    cout << "\n=== 實用範例：清零 ===" << endl;
    double balance = 9999.99;
    cout << "清零前餘額：" << balance << endl;
    set_to_zero(&balance);
    cout << "清零後餘額：" << balance << endl;

    return 0;
}
