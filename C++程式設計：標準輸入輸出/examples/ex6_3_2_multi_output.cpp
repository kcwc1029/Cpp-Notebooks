// ex6_3_2_multi_output.cpp
// 示範一次輸出多個不同型別的值

#include <iostream>
#include <string>
using namespace std;

int main() {
    string name = "陳大明";
    int age = 20;
    double gpa = 3.75;
    char grade = 'A';

    // 各種型別混合輸出
    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << " 歲" << endl;
    cout << "GPA：" << gpa << endl;
    cout << "等第：" << grade << endl;

    // 計算並輸出
    int x = 15, y = 4;
    cout << x << " / " << y << " = " << x / y
         << " 餘 " << x % y << endl;

    return 0;
}
