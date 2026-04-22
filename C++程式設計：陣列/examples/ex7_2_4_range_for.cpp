// ex7_2_4_range_for.cpp
// 示範範圍型 for 迴圈遍歷陣列（C++11）

#include <iostream>
using namespace std;

int main() {
    int scores[] = {85, 92, 78, 95, 88};

    // 傳統 for（需要索引時使用）
    cout << "傳統 for：";
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    // 範圍型 for（只讀，不需要索引時更簡潔）
    cout << "範圍型 for：";
    for (int s : scores) {
        cout << s << " ";
    }
    cout << endl;

    // 範圍型 for（修改元素：需加 & 取參考）
    for (int& s : scores) {
        s += 5;   // 每個成績加 5 分
    }
    cout << "加 5 分後：";
    for (int s : scores) {
        cout << s << " ";
    }
    cout << endl;

    // 計算總和
    double prices[] = {29.9, 49.9, 99.9, 149.9};
    double total = 0;
    for (double p : prices) {
        total += p;
    }
    cout << "\n總價：" << total << endl;

    return 0;
}
