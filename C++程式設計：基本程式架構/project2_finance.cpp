// 專案：個人財務管理系統 v1.0
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void printRow(const string& label, double amount) {
    cout << "║   " << left << setw(12) << label
         << "$ " << right << setw(9) << fixed << setprecision(0) << amount
         << "      ║" << endl;
}

int main() {
    string name;
    int month;

    cout << "╔══════════════════════════════════╗" << endl;
    cout << "║       個人財務管理系統            ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;

    cout << "\n請輸入姓名：";
    cin >> name;
    cout << "請輸入月份（1-12）：";
    cin >> month;

    double salary, partTime, otherIncome;
    cout << "\n【請輸入收入】" << endl;
    cout << "薪資收入：$";  cin >> salary;
    cout << "兼職收入：$";  cin >> partTime;
    cout << "其他收入：$";  cin >> otherIncome;

    double totalIncome = salary + partTime + otherIncome;

    double rent, food, transport, entertainment, otherExpense;
    cout << "\n【請輸入支出】" << endl;
    cout << "房租：$";     cin >> rent;
    cout << "飲食費：$";   cin >> food;
    cout << "交通費：$";   cin >> transport;
    cout << "娛樂費：$";   cin >> entertainment;
    cout << "其他支出：$"; cin >> otherExpense;

    double totalExpense = rent + food + transport + entertainment + otherExpense;
    double balance      = totalIncome - totalExpense;
    double savingRate   = (totalIncome > 0) ? (balance / totalIncome * 100) : 0;

    string advice;
    if      (savingRate >= 30) advice = "優秀，繼續保持！";
    else if (savingRate >= 20) advice = "良好，可以更好";
    else if (savingRate >= 10) advice = "普通，建議減少非必要支出";
    else                       advice = "警告，財務狀況需要注意！";

    cout << "\n╔══════════════════════════════════╗" << endl;
    cout << "║       個人財務月報表              ║" << endl;
    cout << "║  姓名：" << left << setw(4) << name
         << "   " << setw(4) << "2024年 " << month << " 月"
         << "        ║" << endl;
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║ 【收入明細】                      ║" << endl;
    printRow("薪資收入：",  salary);
    printRow("兼職收入：",  partTime);
    printRow("其他收入：",  otherIncome);
    cout << "║   ──────────────────────────      ║" << endl;
    printRow("總收入：",    totalIncome);
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║ 【支出明細】                      ║" << endl;
    printRow("房租：",        rent);
    printRow("飲食費：",      food);
    printRow("交通費：",      transport);
    printRow("娛樂費：",      entertainment);
    printRow("其他支出：",    otherExpense);
    cout << "║   ──────────────────────────      ║" << endl;
    printRow("總支出：",    totalExpense);
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║ 【財務摘要】                      ║" << endl;
    printRow("結餘：",      balance);
    cout << fixed << setprecision(2);
    cout << "║   " << left << setw(10) << "儲蓄率："
         << right << setw(10) << savingRate << "%        ║" << endl;
    cout << "║   評級：" << left << setw(22) << advice << " ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;

    return 0;
}
