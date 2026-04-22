#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    int twd;
    cout << "請輸入台幣金額：";
    cin >> twd;

    // 匯率
    double usd = twd / 30.0;
    double jpy = twd * 4.5;
    double eur = twd / 33.0;
    double gbp = twd / 38.0;

    cout << "台幣：" << twd << " 元" << endl;
    cout << string(27, '=') << endl;
    cout << left << setw(10) << "幣別"
         << right << setw(14) << "換算金額" << endl;
    cout << string(27, '-') << endl;

    cout << fixed << setprecision(2);
    cout << left << setw(10) << "USD" << right << setw(14) << usd << endl;
    cout << left << setw(10) << "JPY" << right << setw(14) << jpy << endl;
    cout << left << setw(10) << "EUR" << right << setw(14) << eur << endl;
    cout << left << setw(10) << "GBP" << right << setw(14) << gbp << endl;
    cout << string(27, '=') << endl;

    return 0;
}