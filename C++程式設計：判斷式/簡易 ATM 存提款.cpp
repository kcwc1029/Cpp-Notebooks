// 練習 4-9：簡易 ATM
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const int CORRECT_PIN = 1234;
    double balance = 10000.0;
    int pin;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    cout << "╔══════════════════╗" << endl;
    cout << "║    歡迎使用 ATM   ║" << endl;
    cout << "╚══════════════════╝" << endl;

    bool unlocked = false;
    while (attempts < MAX_ATTEMPTS) {
        cout << "請輸入密碼：";
        cin >> pin;
        attempts++;
        if (pin == CORRECT_PIN) {
            unlocked = true;
            break;
        } else {
            int remaining = MAX_ATTEMPTS - attempts;
            if (remaining > 0)
                cout << "密碼錯誤，剩餘 " << remaining << " 次機會。" << endl;
        }
    }

    if (!unlocked) {
        cout << "密碼錯誤次數過多，帳戶已鎖定！" << endl;
        return 0;
    }

    cout << "驗證成功！" << endl;

    int choice;
    cout << "\n1. 查詢餘額  2. 存款  3. 提款  4. 離開" << endl;
    cout << "請輸入選項：";
    cin >> choice;

    cout << fixed << setprecision(0);

    switch (choice) {
        case 1:
            cout << "目前餘額：NT$ " << balance << endl;
            break;
        case 2: {
            double amount;
            cout << "請輸入存款金額：NT$ ";
            cin >> amount;
            if (amount <= 0) {
                cout << "存款金額必須為正數！" << endl;
            } else {
                balance += amount;
                cout << "存款成功！餘額：NT$ " << balance << endl;
            }
            break;
        }
        case 3: {
            double amount;
            cout << "請輸入提款金額（1000 的倍數）：NT$ ";
            cin >> amount;
            if (amount <= 0) {
                cout << "金額必須為正數！" << endl;
            } else if (static_cast<int>(amount) % 1000 != 0) {
                cout << "提款金額必須是 1000 的倍數！" << endl;
            } else if (amount > balance) {
                cout << "餘額不足！目前餘額：NT$ " << balance << endl;
            } else {
                balance -= amount;
                cout << "提款成功！餘額：NT$ " << balance << endl;
            }
            break;
        }
        case 4:
            cout << "感謝使用，再見！" << endl;
            break;
        default:
            cout << "無效的選項！" << endl;
    }

    return 0;
}
