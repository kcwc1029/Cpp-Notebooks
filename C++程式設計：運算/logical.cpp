#include <iostream>
using namespace std;

int main() {
    int age = 20;
    double gpa = 3.5;
    bool hasScholarship = true;

    cout << boolalpha;

    // && 應用：所有條件都要成立
    bool canApply = (age >= 18) && (gpa >= 3.0);
    cout << "可申請（18歲以上且GPA≥3.0）：" << canApply << endl;  // true

    // || 應用：至少一個條件成立
    bool getBonus = (gpa >= 3.8) || hasScholarship;
    cout << "獲得獎金（GPA≥3.8 或有獎學金）：" << getBonus << endl; // true

    // ! 應用：條件取反
    bool isMinor = !(age >= 18);
    cout << "是否未成年：" << isMinor << endl;  // false

    // 複合條件
    bool isEligible = (age >= 18) && (age <= 35) && (gpa >= 3.0) && !isMinor;
    cout << "完整資格審查：" << isEligible << endl;  // true

    // 短路求值示範
    cout << "\n=== 短路求值 ===" << endl;
    int x = 0;
    // && 短路：左側為 false，右側不執行
    bool r1 = (x != 0) && (10 / x > 1);   // 不會除以零！
    cout << "短路 &&：" << r1 << endl;     // false（安全）

    // || 短路：左側為 true，右側不執行
    int count = 0;
    bool r2 = (count >= 0) || (++count > 0);  // count 不會被遞增
    cout << "短路 ||：" << r2 << " count=" << count << endl;  // true, count=0

    return 0;
}