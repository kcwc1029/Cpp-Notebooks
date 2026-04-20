// 練習 4-5：分段電費計算
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double kwh;
    cout << "請輸入用電度數：";
    cin >> kwh;

    if (kwh < 0) {
        cout << "錯誤：度數不能為負數" << endl;
        return 1;
    }

    double total = 0;
    double remaining = kwh;

    cout << fixed << setprecision(2);
    cout << "用電：" << kwh << " 度" << endl;
    cout << "電費明細：" << endl;

    if (remaining > 0) {
        double used = (remaining > 120) ? 120 : remaining;
        double cost = used * 1.63;
        total += cost;
        remaining -= used;
        cout << "  1 ~ 120 度（" << used << "度）：NT$ " << cost << endl;
    }
    if (remaining > 0) {
        double used = (remaining > 210) ? 210 : remaining;
        double cost = used * 2.38;
        total += cost;
        remaining -= used;
        cout << "  121 ~ 330 度（" << used << "度）：NT$ " << cost << endl;
    }
    if (remaining > 0) {
        double used = (remaining > 170) ? 170 : remaining;
        double cost = used * 3.52;
        total += cost;
        remaining -= used;
        cout << "  331 ~ 500 度（" << used << "度）：NT$ " << cost << endl;
    }
    if (remaining > 0) {
        double used = (remaining > 200) ? 200 : remaining;
        double cost = used * 4.80;
        total += cost;
        remaining -= used;
        cout << "  501 ~ 700 度（" << used << "度）：NT$ " << cost << endl;
    }
    if (remaining > 0) {
        double cost = remaining * 5.66;
        total += cost;
        cout << "  701 度以上（" << remaining << "度）：NT$ " << cost << endl;
    }

    cout << "應繳電費：NT$ " << total << endl;

    return 0;
}
