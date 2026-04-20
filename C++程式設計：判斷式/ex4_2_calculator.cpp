#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b;
    char op;

    cout << "=== 簡易計算機 ===" << endl;
    cout << "請輸入運算式（例：5.5 + 3）：";
    cin >> a >> op >> b;

    double result;
    bool valid = true;

    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0) {
                cout << "錯誤：除數不能為零！" << endl;
                valid = false;
            } else {
                result = a / b;
            }
            break;
        case '%': {
            int ia = static_cast<int>(a);
            int ib = static_cast<int>(b);
            if (ib == 0) {
                cout << "錯誤：除數不能為零！" << endl;
                valid = false;
            } else {
                result = ia % ib;
            }
            break;
        }
        case '^':
            result = pow(a, b);
            break;
        default:
            cout << "錯誤：未知的運算子 '" << op << "'！" << endl;
            valid = false;
    }

    if (valid) {
        cout << a << " " << op << " " << b << " = " << result << endl;
    }

    return 0;
}
