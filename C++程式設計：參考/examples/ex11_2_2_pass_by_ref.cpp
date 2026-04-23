#include <iostream>
using namespace std;

void addTen(int& n) {       // n 是呼叫者變數的「別名」
    cout << "  [函數內] 修改前 n = " << n << "，位址 = " << &n << endl;
    n += 10;
    cout << "  [函數內] 修改後 n = " << n << endl;
}

void resetToZero(int& val) {
    val = 0;
}

void getInput(int& result) {
    cout << "  請輸入一個整數：";
    cin >> result;    // 直接存入呼叫者的變數
}

int main() {
    int a = 5;
    cout << "=== 傳參考示範 ===" << endl;
    cout << "呼叫前：a = " << a << "，位址 = " << &a << endl;
    addTen(a);
    cout << "呼叫後：a = " << a << endl;    // 變成 15！

    cout << endl;

    int score = 95;
    cout << "重置前：score = " << score << endl;
    resetToZero(score);
    cout << "重置後：score = " << score << endl;    // 0

    cout << endl;

    int userValue;
    cout << "透過參考接收輸入：" << endl;
    getInput(userValue);
    cout << "  userValue = " << userValue << endl;

    cout << "\n=== 結論 ===" << endl;
    cout << "傳參考時，函數拿到的是原始變數的別名" << endl;
    cout << "函數內的修改「會直接影響」原始變數" << endl;

    return 0;
}
