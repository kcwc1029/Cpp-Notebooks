#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;

    bool isGreater = (x > y);
    bool isEqual   = (x == y);
    bool notEqual  = (x != y);

    cout << boolalpha;
    cout << "x > y  : " << isGreater << endl;
    cout << "x == y : " << isEqual   << endl;
    cout << "x != y : " << notEqual  << endl;

    bool isTeen = (x >= 13 && x <= 19);
    if (isTeen) {
        cout << x << " 是青少年" << endl;
    } else {
        cout << x << " 不是青少年" << endl;
    }

    // Truthy / Falsy 示範
    cout << "\n=== 真假值示範 ===" << endl;
    if (1)    cout << "1 是 true"   << endl;
    if (0)    cout << "不會印出"    << endl;
    if (-5)   cout << "-5 是 true"  << endl;
    if (3.14) cout << "3.14 是 true"<< endl;

    return 0;
}
