// 練習 2-4：時間換算
#include <iostream>
using namespace std;

int main() {
    int totalSeconds;

    cout << "請輸入秒數：";
    cin >> totalSeconds;

    int hours   = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    cout << totalSeconds << " 秒 = "
         << hours   << " 小時 "
         << minutes << " 分 "
         << seconds << " 秒" << endl;

    return 0;
}
