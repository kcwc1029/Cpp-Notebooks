// ex6_1_2_cin_types.cpp
// 示範 cin 讀取各種資料型別

#include <iostream>
using namespace std;

int main() {
    int    n;
    double d;
    char   c;
    bool   b;

    cout << "輸入整數：";
    cin >> n;
    cout << "你輸入了整數：" << n << endl;

    cout << "輸入浮點數：";
    cin >> d;
    cout << "你輸入了浮點數：" << d << endl;

    cout << "輸入單一字元：";
    cin >> c;   // 會跳過空白，只讀一個字元
    cout << "你輸入了字元：" << c << endl;

    cout << "輸入布林（0 或 1）：";
    cin >> b;
    cout << "你輸入了布林：" << b << endl;

    return 0;
}
