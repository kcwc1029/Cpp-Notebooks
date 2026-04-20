// 練習 2-10：個人資料卡
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string name, idNumber, birthday, phone, address;

    cout << "=== 個人資料填寫 ===" << endl;
    cout << "姓名：";               getline(cin, name);
    cout << "身分證字號：";         getline(cin, idNumber);
    cout << "生日（yyyy/mm/dd）："; getline(cin, birthday);
    cout << "電話：";               getline(cin, phone);
    cout << "地址：";               getline(cin, address);

    string line(40, '=');
    cout << "\n" << line << endl;
    cout << left;
    cout << "║ " << setw(10) << "姓名"     << "│ " << setw(24) << name      << "║" << endl;
    cout << "║ " << setw(10) << "身分證字號" << "│ " << setw(24) << idNumber << "║" << endl;
    cout << "║ " << setw(10) << "生日"     << "│ " << setw(24) << birthday  << "║" << endl;
    cout << "║ " << setw(10) << "電話"     << "│ " << setw(24) << phone     << "║" << endl;
    cout << "║ " << setw(10) << "地址"     << "│ " << setw(24) << address   << "║" << endl;
    cout << line << endl;

    return 0;
}
