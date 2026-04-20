#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入四位數：";
    cin >> n;

    int thousands = n / 1000;
    int hundreds  = (n / 100) % 10;
    int tens      = (n / 10)  % 10;
    int ones      = n % 10;

    cout << "千位：" << thousands << endl;
    cout << "百位：" << hundreds  << endl;
    cout << "十位：" << tens      << endl;
    cout << "個位：" << ones      << endl;
    cout << "各位數字和：" << (thousands + hundreds + tens + ones) << endl;

    bool isPalindrome = (thousands == ones) && (hundreds == tens);
    cout << "是否為對稱數：" << (isPalindrome ? "是" : "否") << endl;

    return 0;
}