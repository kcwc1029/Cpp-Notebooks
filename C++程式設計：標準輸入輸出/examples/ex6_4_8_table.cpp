// ex6_4_8_table.cpp
// 示範格式化表格輸出（setw + setfill + fixed + left/right 綜合應用）

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // 商品清單
    string items[]    = {"筆記型電腦", "滑鼠", "鍵盤", "螢幕"};
    int    quantity[] = {1, 2, 1, 2};
    double price[]    = {32000.0, 299.0, 1500.0, 5999.0};
    int n = 4;

    // 表頭
    cout << string(45, '=') << endl;
    cout << left
         << setw(12) << "商品名稱"
         << right
         << setw(6)  << "數量"
         << setw(10) << "單價"
         << setw(12) << "小計"
         << endl;
    cout << string(45, '-') << endl;

    double total = 0.0;

    // 資料列
    for (int i = 0; i < n; i++) {
        double subtotal = quantity[i] * price[i];
        total += subtotal;

        cout << left  << setw(12) << items[i]
             << right << fixed << setprecision(0)
             << setw(6)  << quantity[i]
             << setw(10) << price[i]
             << setw(12) << subtotal
             << endl;
    }

    // 總計
    cout << string(45, '-') << endl;
    cout << left  << setw(18) << "合計"
         << right << setw(12) << total << endl;

    double tax   = total * 0.05;
    double grand = total + tax;
    cout << left  << setw(18) << "稅額（5%）"
         << right << setw(12) << tax << endl;
    cout << string(45, '-') << endl;
    cout << left  << setw(18) << "總計（含稅）"
         << right << setw(12) << grand << endl;
    cout << string(45, '=') << endl;

    return 0;
}
