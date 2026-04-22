#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;

    cout << "請輸入 n（1~9）：";
    cin >> n;

    cout << n << " 的乘法表" << endl;
    cout << string(18, '\xe2\x94\x80') << endl;   // ──────────────────

    for (int i = 1; i <= 9; i++) {
        cout << n << " × " << i << " = "
             << setw(2) << n * i << endl;
    }

    return 0;
}