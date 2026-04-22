// ex6_4_7_showpos.cpp
// 示範 showpos 讓正數顯示 + 號

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int values[] = {-10, 0, 5, 100};

    cout << "不顯示正號：" << endl;
    for (int v : values) {
        cout << setw(6) << v << endl;
    }

    cout << "\n顯示正號（showpos）：" << endl;
    cout << showpos;
    for (int v : values) {
        cout << setw(6) << v << endl;
    }

    cout << noshowpos;   // 取消 showpos

    cout << "\n浮點數加正號：" << endl;
    cout << showpos << fixed << setprecision(2);
    double temps[] = {-5.5, 0.0, 22.3, 36.8};
    for (double t : temps) {
        cout << setw(8) << t << " °C" << endl;
    }

    return 0;
}
