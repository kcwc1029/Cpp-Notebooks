// 練習 4-4：Zeller 公式求星期幾
#include <iostream>
using namespace std;

int main() {
    int year, month, day;
    cout << "請輸入日期（年 月 日）：";
    cin >> year >> month >> day;

    if (month <= 2) {
        year--;
        month += 12;
    }

    int K = year % 100;
    int J = year / 100;
    int h = (day + (13*(month+1)/5) + K + K/4 + J/4 - 2*J) % 7;
    if (h < 0) h += 7;

    string days[] = {"星期六","星期日","星期一","星期二","星期三","星期四","星期五"};

    // 輸出原始月份（已被修改，需反向還原顯示）
    cout << year + (month > 12 ? 1 : 0) << "年"
         << (month > 12 ? month - 12 : month) << "月"
         << day << "日是 " << days[h] << endl;

    return 0;
}
