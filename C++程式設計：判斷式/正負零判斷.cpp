// 練習 4-1：正負零判斷
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入一個整數：";
    cin >> n;

    if (n > 0) {
        cout << n << " 是正數" << endl;
    } else if (n < 0) {
        cout << n << " 是負數" << endl;
    } else {
        cout << n << " 是零" << endl;
    }

    return 0;
}
