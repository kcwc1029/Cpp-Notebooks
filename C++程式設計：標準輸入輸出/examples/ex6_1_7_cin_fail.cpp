// ex6_1_7_cin_fail.cpp
// 示範 cin 的錯誤狀態偵測與處理

#include <iostream>
using namespace std;

int main() {
    int num;

    cout << "請輸入整數：";
    cin >> num;

    if (cin.fail()) {
        cout << "輸入錯誤！請輸入整數。" << endl;
        cin.clear();               // 清除錯誤旗標，恢復 cin 正常狀態
        cin.ignore(1000, '\n');    // 丟棄錯誤的輸入，直到換行
    } else {
        cout << "你輸入了：" << num << endl;
    }

    return 0;
}
