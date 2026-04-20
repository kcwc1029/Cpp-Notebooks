#include <iostream>
using namespace std;

int main() {
    // 短路求值防止除以零
    int divisor = 0;
    int dividend = 10;

    if (divisor != 0 && dividend / divisor > 2) {
        cout << "商大於 2" << endl;
    } else {
        cout << "除數為零，跳過計算" << endl;
    }

    // 示範短路不執行右側
    int counter = 0;

    // false && ... → 右側不執行
    bool r1 = false && (++counter > 0);
    cout << "false && ++counter，counter = " << counter << endl; // 0

    // true || ... → 右側不執行
    bool r2 = true || (++counter > 0);
    cout << "true || ++counter，counter = " << counter << endl;  // 仍 0

    // true && ... → 右側會執行
    bool r3 = true && (++counter > 0);
    cout << "true && ++counter，counter = " << counter << endl;  // 1

    // 安全存取字串
    string s = "";
    if (!s.empty() && s[0] == 'A') {
        cout << "以 A 開頭" << endl;
    } else {
        cout << "字串為空或不以 A 開頭" << endl;
    }

    return 0;
}
