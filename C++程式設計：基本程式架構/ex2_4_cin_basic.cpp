#include <iostream>
#include <string>
using namespace std;

int main() {
    int age;
    double height;
    string name;

    cout << "請輸入你的名字：";
    cin >> name;

    cout << "請輸入你的年齡：";
    cin >> age;

    cout << "請輸入你的身高（cm）：";
    cin >> height;

    cout << "\n=== 基本資料 ===" << endl;
    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << " 歲" << endl;
    cout << "身高：" << height << " cm" << endl;

    return 0;
}
