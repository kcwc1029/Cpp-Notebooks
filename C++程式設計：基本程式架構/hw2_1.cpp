// 練習 2-1：自我介紹程式
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name, department;
    int age;

    cout << "姓名：";
    cin >> name;
    cout << "年齡：";
    cin >> age;
    cin.ignore();
    cout << "科系：";
    getline(cin, department);

    cout << "==========================" << endl;
    cout << "大家好，我是 " << name << "！" << endl;
    cout << "我今年 " << age << " 歲" << endl;
    cout << "目前就讀 " << department << endl;
    cout << "很高興認識大家！" << endl;
    cout << "==========================" << endl;

    return 0;
}
