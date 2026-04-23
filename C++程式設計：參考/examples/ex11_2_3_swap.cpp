#include <iostream>
#include <string>
using namespace std;

// ❌ 傳值：無效的交換
void swap_bad(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "  [swap_bad 內] a=" << a << ", b=" << b << "（只是副本）" << endl;
}

// ✅ 傳參考：有效的交換
void swap_good(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// ✅ 模板版本：可以交換任何型別
template <typename T>
void my_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;

    cout << "=== 傳值交換（無效）===" << endl;
    cout << "呼叫前：x=" << x << ", y=" << y << endl;
    swap_bad(x, y);
    cout << "呼叫後：x=" << x << ", y=" << y << "（沒有改變！）" << endl;

    cout << "\n=== 傳參考交換（有效）===" << endl;
    cout << "呼叫前：x=" << x << ", y=" << y << endl;
    swap_good(x, y);
    cout << "呼叫後：x=" << x << ", y=" << y << "（成功交換！）" << endl;

    cout << "\n=== 模板交換（泛用版本）===" << endl;
    double a = 1.5, b = 2.5;
    cout << "交換前：a=" << a << ", b=" << b << endl;
    my_swap(a, b);
    cout << "交換後：a=" << a << ", b=" << b << endl;

    string s1 = "Hello", s2 = "World";
    cout << "交換前：s1=" << s1 << ", s2=" << s2 << endl;
    my_swap(s1, s2);
    cout << "交換後：s1=" << s1 << ", s2=" << s2 << endl;

    // 標準庫也提供了 std::swap，用法相同
    cout << "\n=== 使用標準庫 std::swap ===" << endl;
    int p = 100, q = 200;
    cout << "交換前：p=" << p << ", q=" << q << endl;
    swap(p, q);    // 標準庫版本
    cout << "交換後：p=" << p << ", q=" << q << endl;

    return 0;
}
