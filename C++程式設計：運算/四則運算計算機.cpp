#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int a, b;
    cout << "請輸入兩個整數：";
    cin >> a >> b;

    cout << fixed << setprecision(4);
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << " (整數除法)" << endl;
    cout << "a / b = " << static_cast<double>(a) / b << " (浮點除法)" << endl;
    cout << "a % b = " << a % b << endl;

    return 0;
}