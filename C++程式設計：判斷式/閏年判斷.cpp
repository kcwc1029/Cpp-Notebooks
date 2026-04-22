// 練習 4-2：閏年判斷
#include <iostream>
using namespace std;

int main() {
    int year;
    cout << "請輸入年份：";
    cin >> year;

    bool isLeap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

    if (isLeap) {
        cout << year << " 是閏年（366 天）" << endl;
    } else {
        cout << year << " 不是閏年（365 天）" << endl;
    }

    return 0;
}
