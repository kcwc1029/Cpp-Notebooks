// ex6_1_1_cin_basic.cpp
// 示範 cin 的基本用法：讀取整數

#include <iostream>
using namespace std;

int main() {
    int age;
    cout << "請輸入你的年齡：";
    cin >> age;
    cout << "你輸入的年齡是：" << age << endl;
    return 0;
}
