#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "請輸入你的分數：";
    cin >> score;

    if (score >= 60) {
        cout << "恭喜！你及格了！" << endl;
    }

    if (score == 100) {
        cout << "完美分數！太厲害了！" << endl;
    }

    cout << "程式結束。" << endl;
    return 0;
}
