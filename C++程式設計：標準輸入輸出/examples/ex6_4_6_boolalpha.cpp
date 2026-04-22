// ex6_4_6_boolalpha.cpp
// 示範 boolalpha 讓布林值顯示為 true/false

#include <iostream>
using namespace std;

int main() {
    bool a = true, b = false;

    cout << "預設：" << a << " " << b << endl;            // 1 0

    cout << boolalpha;
    cout << "boolalpha：" << a << " " << b << endl;       // true false

    cout << noboolalpha;
    cout << "noboolalpha：" << a << " " << b << endl;     // 1 0

    // 配合 cin 用 boolalpha 讀取 true/false 字串
    bool result;
    cout << boolalpha;
    cout << "請輸入 true 或 false：";
    cin >> result;
    cout << "你輸入了：" << result << endl;

    return 0;
}
