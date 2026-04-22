#include <iostream>
using namespace std;

int main() {
    // 整數除法陷阱示範
    int a = 7, b = 2;

    cout << "整數除法 7/2 = " << a / b << endl;
    cout << "強制轉型後  = " << static_cast<double>(a) / b << endl;

    // 字元與整數的關係
    char c = 'A';
    cout << "\n字元 'A' 的 ASCII 值：" << static_cast<int>(c) << endl;

    int ascii = 66;
    cout << "ASCII 66 對應的字元：" << static_cast<char>(ascii) << endl;

    // 截斷小數
    double pi = 3.14159;
    int truncated = static_cast<int>(pi);
    cout << "\nPI 截斷後：" << truncated << endl;

    return 0;
}
