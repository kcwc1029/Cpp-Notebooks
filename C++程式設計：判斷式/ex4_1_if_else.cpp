#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "請輸入你的分數：";
    cin >> score;

    if (score >= 60) {
        cout << "及格" << endl;
    } else {
        cout << "不及格" << endl;
    }

    int num;
    cout << "請輸入一個整數：";
    cin >> num;

    if (num % 2 == 0) {
        cout << num << " 是偶數" << endl;
    } else {
        cout << num << " 是奇數" << endl;
    }

    return 0;
}
