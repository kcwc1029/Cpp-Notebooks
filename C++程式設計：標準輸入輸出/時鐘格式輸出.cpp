#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int h, m, s;

    cout << "請輸入時：";
    cin >> h;
    cout << "請輸入分：";
    cin >> m;
    cout << "請輸入秒：";
    cin >> s;

    // setfill('0') + setw(2) 自動補零
    cout << setfill('0')
         << setw(2) << h << ":"
         << setw(2) << m << ":"
         << setw(2) << s << endl;

    return 0;
}