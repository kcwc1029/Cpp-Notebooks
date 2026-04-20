// 練習 2-8：匯率換算機
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const double TWD_TO_USD = 1.0 / 30.0;
    const double TWD_TO_JPY = 4.5;
    const double TWD_TO_EUR = 1.0 / 33.0;

    double twd;
    cout << "請輸入台幣金額：NT$";
    cin >> twd;

    cout << fixed << setprecision(2);
    cout << "\n=== 匯率換算結果 ===" << endl;
    cout << "台幣：NT$ " << twd << endl;
    cout << "美元：USD " << twd * TWD_TO_USD << endl;
    cout << "日圓：JPY " << twd * TWD_TO_JPY << endl;
    cout << "歐元：EUR " << twd * TWD_TO_EUR << endl;

    return 0;
}
