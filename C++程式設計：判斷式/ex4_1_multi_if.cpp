#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "請輸入分數（0-100）：";
    cin >> score;

    char grade;
    if      (score >= 90) grade = 'A';
    else if (score >= 80) grade = 'B';
    else if (score >= 70) grade = 'C';
    else if (score >= 60) grade = 'D';
    else                  grade = 'F';

    cout << "等級：" << grade << endl;

    if (grade == 'A') {
        cout << "優秀！繼續保持！" << endl;
    } else if (grade == 'B') {
        cout << "不錯！再加把勁！" << endl;
    } else if (grade == 'C') {
        cout << "及格，但還有進步空間。" << endl;
    } else if (grade == 'D') {
        cout << "剛好及格，需要加強。" << endl;
    } else {
        cout << "不及格，請找老師補救。" << endl;
    }

    return 0;
}
