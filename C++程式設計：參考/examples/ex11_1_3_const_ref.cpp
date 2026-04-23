#include <iostream>
using namespace std;

int main() {
    int x = 42;

    // 一般參考 vs const 參考
    int&       r  = x;
    const int& cr = x;

    r = 100;            // ✅ 可以修改
    cout << "r = 100 後，x = " << x << endl;

    // cr = 200;        // ❌ 錯誤！const 參考不能修改
    cout << "cr = " << cr << endl;   // ✅ 可以讀取

    // const 參考可以綁定字面值（一般參考不行）
    const int& lit = 42;
    // int& bad = 42;   // ❌ 錯誤！非 const 參考不能綁定字面值
    cout << "\nconst 參考綁定字面值 42：lit = " << lit << endl;

    // const 參考可以綁定運算結果（臨時值）
    const int& expr = x + 10;
    // int& bad2 = x + 10;   // ❌ 錯誤！
    cout << "const 參考綁定 x+10：expr = " << expr << endl;

    // const 參考可以綁定不同型別（隱含型別轉換）
    double d = 3.14;
    const int& di = d;    // 建立臨時 int，值為 3（截斷）
    // int& di2 = d;       // ❌ 錯誤！一般參考不允許型別不符
    cout << "\nconst int& 綁定 double 3.14：di = " << di << endl;

    // const 參考延長臨時物件的生命期
    const int& temp = (x * 2 + 5);
    cout << "const 參考綁定 x*2+5：temp = " << temp << endl;

    cout << "\n=== 總結 ===" << endl;
    cout << "非 const 參考：只能綁定可修改的左值" << endl;
    cout << "const 參考：可以綁定左值、右值、字面值、不同型別" << endl;

    return 0;
}
