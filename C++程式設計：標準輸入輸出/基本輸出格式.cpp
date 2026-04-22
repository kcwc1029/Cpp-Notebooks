#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string name;
    int studentId, chinese, math, english;

    cout << "姓名：";
    cin.ignore();
    getline(cin, name);

    cout << "學號：";
    cin >> studentId;

    cout << "國文：";
    cin >> chinese;

    cout << "數學：";
    cin >> math;

    cout << "英文：";
    cin >> english;

    double avg = (chinese + math + english) / 3.0;

    cout << "╔══════════════════════════════╗" << endl;
    cout << "║          學生成績單           ║" << endl;
    cout << "╠══════════════════════════════╣" << endl;
    cout << "║ 姓名：" << left << setw(23) << name << "║" << endl;
    cout << "║ 學號：" << left << setw(23) << studentId << "║" << endl;
    cout << "╠══════════════════════════════╣" << endl;
    cout << "║ 國文：" << right << setw(4) << chinese << " 分"
         << setw(17) << left << "" << "║" << endl;
    cout << "║ 數學：" << right << setw(4) << math    << " 分"
         << setw(17) << left << "" << "║" << endl;
    cout << "║ 英文：" << right << setw(4) << english << " 分"
         << setw(17) << left << "" << "║" << endl;
    cout << "╠══════════════════════════════╣" << endl;
    cout << fixed << setprecision(2);
    cout << "║ 平均：" << right << setw(7) << avg << " 分"
         << setw(14) << left << "" << "║" << endl;
    cout << "╚══════════════════════════════╝" << endl;

    return 0;
}