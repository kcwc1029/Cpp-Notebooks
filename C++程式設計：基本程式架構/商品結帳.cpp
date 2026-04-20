// 練習 2-5：商品結帳
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string productName;
    double unitPrice;
    int quantity;

    cout << "商品名稱：";
    getline(cin, productName);
    cout << "單價：";
    cin >> unitPrice;
    cout << "數量：";
    cin >> quantity;

    double subtotal = unitPrice * quantity;
    double tax      = subtotal * 0.05;
    double total    = subtotal + tax;

    cout << fixed << setprecision(0);
    cout << "========== 收據 ==========" << endl;
    cout << "商品：" << productName << endl;
    cout << "單價：$" << unitPrice << endl;
    cout << "數量：" << quantity << endl;
    cout << "--------------------------" << endl;
    cout << "小計：$" << subtotal << endl;
    cout << "稅額（5%）：$" << tax << endl;
    cout << "總計：$" << total << endl;
    cout << "==========================" << endl;

    return 0;
}
