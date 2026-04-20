#include <iostream>
using namespace std;

int main() {
    char grade;
    cout << "請輸入等級（A/B/C/D/F）：";
    cin >> grade;

    switch (grade) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            cout << "及格" << endl;
            break;
        case 'F':
            cout << "不及格" << endl;
            break;
        default:
            cout << "無效的等級" << endl;
    }

    // 示範忘記 break 造成的 fall-through
    int x = 2;
    cout << "\n示範忘記 break 的結果（x=2）：" << endl;
    switch (x) {
        case 1:
            cout << "Case 1" << endl;
        case 2:
            cout << "Case 2" << endl;
        case 3:
            cout << "Case 3" << endl;
        default:
            cout << "Default" << endl;
    }

    return 0;
}
