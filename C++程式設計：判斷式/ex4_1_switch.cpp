#include <iostream>
using namespace std;

int main() {
    int day;
    cout << "請輸入星期幾（1-7）：";
    cin >> day;

    switch (day) {
        case 1:
            cout << "星期一：開始新的一週，加油！" << endl;
            break;
        case 2:
            cout << "星期二：繼續努力！" << endl;
            break;
        case 3:
            cout << "星期三：已經過了一半了！" << endl;
            break;
        case 4:
            cout << "星期四：快到週末了！" << endl;
            break;
        case 5:
            cout << "星期五：TGIF！今晚要慶祝嗎？" << endl;
            break;
        case 6:
        case 7:
            cout << "週末！好好休息！" << endl;
            break;
        default:
            cout << "輸入錯誤，請輸入 1-7。" << endl;
            break;
    }

    return 0;
}
