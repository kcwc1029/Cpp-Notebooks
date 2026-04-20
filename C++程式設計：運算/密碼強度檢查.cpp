#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string password;
    cout << "請輸入密碼：";
    cin >> password;

    bool hasLength  = (password.length() >= 8);
    bool hasDigit   = false;
    bool hasUpper   = false;
    bool hasLower   = false;
    bool hasSpecial = false;

    for (char c : password) {
        if (isdigit(c))  hasDigit   = true;
        if (isupper(c))  hasUpper   = true;
        if (islower(c))  hasLower   = true;
        if (!isalnum(c)) hasSpecial = true;
    }

    int score = hasLength + hasDigit + hasUpper + hasLower + hasSpecial;

    cout << "\n=== 密碼強度分析 ===" << endl;
    cout << "長度 ≥ 8：" << (hasLength  ? "✓" : "✗") << endl;
    cout << "含數字："   << (hasDigit   ? "✓" : "✗") << endl;
    cout << "含大寫："   << (hasUpper   ? "✓" : "✗") << endl;
    cout << "含小寫："   << (hasLower   ? "✓" : "✗") << endl;
    cout << "含特殊字元：" << (hasSpecial ? "✓" : "✗") << endl;
    cout << "滿足條件：" << score << "/5" << endl;

    string strength = (score <= 2) ? "弱" :
                      (score <= 4) ? "中等" : "強";
    cout << "密碼強度：" << strength << endl;

    return 0;
}