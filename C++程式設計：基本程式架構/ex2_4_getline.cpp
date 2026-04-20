#include <iostream>
#include <string>
using namespace std;

int main() {
    string fullName;
    string address;
    int age;

    cout << "請輸入年齡：";
    cin >> age;
    cin.ignore();   // 清除輸入緩衝區中殘留的換行符號

    cout << "請輸入全名（含空格）：";
    getline(cin, fullName);

    cout << "請輸入地址：";
    getline(cin, address);

    cout << "\n=== 資料確認 ===" << endl;
    cout << "年齡：" << age << endl;
    cout << "姓名：" << fullName << endl;
    cout << "地址：" << address << endl;

    return 0;
}
