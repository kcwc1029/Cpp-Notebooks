// ex6_1_4_getline.cpp
// 示範 getline 讀取整行字串（含空格）

#include <iostream>
#include <string>
using namespace std;

int main() {
    string fullName;
    string address;

    cout << "請輸入全名（可含空格）：";
    getline(cin, fullName);

    cout << "請輸入地址：";
    getline(cin, address);

    cout << "\n=== 資料確認 ===" << endl;
    cout << "姓名：" << fullName << endl;
    cout << "地址：" << address << endl;

    return 0;
}
