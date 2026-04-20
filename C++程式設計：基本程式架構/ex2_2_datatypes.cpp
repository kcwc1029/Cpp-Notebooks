#include <iostream>
#include <string>
using namespace std;

int main() {
    // 整數
    int age = 20;
    long long population = 8000000000LL;

    // 浮點數
    double height = 175.5;
    float temperature = 36.6f;

    // 字元
    char grade = 'A';

    // 布林
    bool isStudent = true;

    // 字串
    string name = "Alice";

    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << endl;
    cout << "身高：" << height << " cm" << endl;
    cout << "體溫：" << temperature << " °C" << endl;
    cout << "成績：" << grade << endl;
    cout << "是學生：" << isStudent << endl;
    cout << "全球人口：" << population << endl;

    return 0;
}
