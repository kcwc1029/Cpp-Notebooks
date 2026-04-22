#include <iostream>
using namespace std;

int main() {
    int num;
    bool valid = false;

    while (!valid) {
        cout << "請輸入 1 到 100 之間的整數：";
        cin >> num;

        if (cin.fail()) {
            // 輸入的不是整數
            cerr << "[錯誤] 請輸入整數！" << endl;
            cin.clear();              // 清除錯誤旗標
            cin.ignore(1000, '\n');   // 丟棄錯誤輸入
        } else if (num < 1 || num > 100) {
            // 整數但超出範圍
            cerr << "[錯誤] 數值超出範圍（1~100）！" << endl;
            cin.ignore(1000, '\n');
        } else {
            valid = true;
        }
    }

    cout << "輸入成功：" << num << endl;

    return 0;
}