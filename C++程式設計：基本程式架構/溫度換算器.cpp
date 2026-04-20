// 練習 2-2：溫度換算器
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double celsius;

    cout << "請輸入攝氏溫度：";
    cin >> celsius;

    double fahrenheit = celsius * 9.0 / 5.0 + 32;
    double kelvin = celsius + 273.15;

    cout << fixed << setprecision(2);
    cout << "攝氏：" << setw(8) << celsius    << " °C" << endl;
    cout << "華氏：" << setw(8) << fahrenheit << " °F" << endl;
    cout << "克氏：" << setw(8) << kelvin     << " K"  << endl;

    return 0;
}
