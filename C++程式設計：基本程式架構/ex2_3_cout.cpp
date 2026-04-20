#include <iostream>
using namespace std;

int main() {
    int age = 21;
    double gpa = 3.85;
    char gender = 'M';
    bool isEnrolled = true;
    string name = "Bob";

    cout << "=== 學生資料 ===" << endl;
    cout << "姓名：" << name << "\n";
    cout << "年齡：" << age << "\n";
    cout << "GPA：" << gpa << "\n";
    cout << "性別：" << gender << "\n";
    cout << "在學：" << isEnrolled << "\n";

    cout << boolalpha;
    cout << "在學（文字）：" << isEnrolled << "\n";

    return 0;
}
