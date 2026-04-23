#include <iostream>
using namespace std;

void addTen(int n) {        // n 是呼叫者變數的「副本」
    cout << "  [函數內] 修改前 n = " << n << "，位址 = " << &n << endl;
    n += 10;
    cout << "  [函數內] 修改後 n = " << n << endl;
}   // n 在此銷毀，原始變數不受影響

void tryDouble(int x) {
    x *= 2;
    cout << "  [tryDouble 內] x = " << x << endl;
}

int main() {
    int a = 5;
    cout << "=== 傳值示範 ===" << endl;
    cout << "呼叫前：a = " << a << "，位址 = " << &a << endl;
    addTen(a);
    cout << "呼叫後：a = " << a << endl;    // 仍然是 5！

    cout << endl;

    int b = 10;
    cout << "呼叫前：b = " << b << endl;
    tryDouble(b);
    cout << "呼叫後：b = " << b << endl;    // 仍然是 10！

    cout << "\n=== 結論 ===" << endl;
    cout << "傳值時，函數只拿到副本" << endl;
    cout << "函數內的修改「不會」影響原始變數" << endl;

    return 0;
}
