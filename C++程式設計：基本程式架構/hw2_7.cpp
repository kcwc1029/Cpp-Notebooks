// 練習 2-7：成績格式化表格
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const int N = 3;
    string names[N];
    int chinese[N], math[N], english[N];

    for (int i = 0; i < N; i++) {
        cout << "輸入第 " << i + 1 << " 位學生姓名：";
        cin >> names[i];
        cout << "國文 數學 英文：";
        cin >> chinese[i] >> math[i] >> english[i];
    }

    cout << "\n╔═══════════╦══════╦══════╦══════╦════╗" << endl;
    cout <<   "║ " << left << setw(9) << "姓名"
         << " ║ " << setw(4) << "國文"
         << " ║ " << setw(4) << "數學"
         << " ║ " << setw(4) << "英文"
         << " ║ " << setw(2) << "均" << " ║" << endl;
    cout << "╠═══════════╬══════╬══════╬══════╬════╣" << endl;

    for (int i = 0; i < N; i++) {
        int avg = (chinese[i] + math[i] + english[i]) / 3;
        cout << "║ " << left  << setw(9) << names[i]
             << " ║ " << right << setw(4) << chinese[i]
             << " ║ " << setw(4) << math[i]
             << " ║ " << setw(4) << english[i]
             << " ║ " << setw(2) << avg << " ║" << endl;
    }

    cout << "╚═══════════╩══════╩══════╩══════╩════╝" << endl;

    return 0;
}
