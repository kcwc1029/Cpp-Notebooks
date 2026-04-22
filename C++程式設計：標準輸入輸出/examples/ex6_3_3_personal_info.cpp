// ex6_3_3_personal_info.cpp
// 綜合輸出入範例：混合 cin >> 和 getline 讀取個人資料

#include <iostream>
#include <string>
using namespace std;

int main() {
    string name, department, hometown;
    int age, studentId;
    double gpa;

    cout << "===== 學生資料輸入 =====" << endl;

    cout << "學號：";
    cin >> studentId;

    cout << "年齡：";
    cin >> age;

    cin.ignore();   // 清除數字後的換行符，確保 getline 正常運作

    cout << "姓名：";
    getline(cin, name);

    cout << "科系：";
    getline(cin, department);

    cout << "家鄉：";
    getline(cin, hometown);

    cout << "GPA：";
    cin >> gpa;

    cout << "\n===== 學生資料輸出 =====" << endl;
    cout << "學號：" << studentId << endl;
    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << " 歲" << endl;
    cout << "科系：" << department << endl;
    cout << "家鄉：" << hometown << endl;
    cout << "GPA：" << gpa << endl;

    return 0;
}
