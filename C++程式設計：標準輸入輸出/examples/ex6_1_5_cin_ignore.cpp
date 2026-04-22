// ex6_1_5_cin_ignore.cpp
// 示範 cin >> 與 getline 混用時，需要 cin.ignore() 清除緩衝區換行符

#include <iostream>
#include <string>
using namespace std;

int main() {
    int age;
    string name;

    cout << "請輸入年齡：";
    cin >> age;

    cin.ignore();   // 清除緩衝區中的換行符，避免 getline 提早結束

    cout << "請輸入全名：";
    getline(cin, name);

    cout << "年齡：" << age << "，姓名：" << name << endl;

    return 0;
}
