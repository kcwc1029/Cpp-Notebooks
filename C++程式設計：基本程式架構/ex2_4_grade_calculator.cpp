#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string studentName;
    int studentID;
    double math, english, science;

    cout << "╔══════════════════════╗" << endl;
    cout << "║   學生成績計算系統   ║" << endl;
    cout << "╚══════════════════════╝" << endl;

    cout << "\n請輸入學號：";
    cin >> studentID;
    cin.ignore();

    cout << "請輸入學生姓名：";
    getline(cin, studentName);

    cout << "請輸入數學成績：";
    cin >> math;
    cout << "請輸入英文成績：";
    cin >> english;
    cout << "請輸入自然成績：";
    cin >> science;

    double average = (math + english + science) / 3.0;

    char letterGrade;
    if      (average >= 90) letterGrade = 'A';
    else if (average >= 80) letterGrade = 'B';
    else if (average >= 70) letterGrade = 'C';
    else if (average >= 60) letterGrade = 'D';
    else                    letterGrade = 'F';

    cout << fixed << setprecision(1);
    cout << "\n=== 成績報告 ===" << endl;
    cout << "學號：" << studentID << endl;
    cout << "姓名：" << studentName << endl;
    cout << "────────────────" << endl;
    cout << setw(8) << left << "數學" << math << endl;
    cout << setw(8) << left << "英文" << english << endl;
    cout << setw(8) << left << "自然" << science << endl;
    cout << "────────────────" << endl;
    cout << setw(8) << left << "平均" << average << endl;
    cout << setw(8) << left << "等級" << letterGrade << endl;

    return 0;
}
