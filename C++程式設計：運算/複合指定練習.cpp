#include <iostream>
using namespace std;

int main() {
    int money = 1000;
    cout << "初始：" << money << endl;

    money += 500;
    cout << "加 500 後：" << money << endl;    // 1500

    money *= 2;
    cout << "乘以 2 後：" << money << endl;    // 3000

    money -= 300;
    cout << "減 300 後：" << money << endl;    // 2700

    money /= 3;
    cout << "除以 3 後：" << money << endl;    // 900

    money %= 7;
    cout << "取 7 的餘後：" << money << endl;  // 900 % 7 = 5

    return 0;
}