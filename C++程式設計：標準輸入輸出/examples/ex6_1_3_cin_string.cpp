// ex6_1_3_cin_string.cpp
// 示範 cin 讀取字串（遇空白停止）

#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName, lastName;

    cout << "請輸入姓氏：";
    cin >> lastName;

    cout << "請輸入名字：";
    cin >> firstName;

    cout << "你好，" << lastName << firstName << "！" << endl;

    return 0;
}
