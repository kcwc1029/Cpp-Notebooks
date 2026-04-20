#include <iostream>
#include <string>
using namespace std;

int main() {
    int score;
    cout << "請輸入分數：";
    cin >> score;

    // 基本三元運算子
    string result = (score >= 60) ? "及格" : "不及格";
    cout << result << endl;

    // 巢狀三元（多等級）
    string grade = (score >= 90) ? "A" :
                   (score >= 80) ? "B" :
                   (score >= 70) ? "C" :
                   (score >= 60) ? "D" : "F";
    cout << "等級：" << grade << endl;

    // 嵌入在輸出中
    int num;
    cout << "請輸入一個整數：";
    cin >> num;
    cout << num << " 是 " << (num % 2 == 0 ? "偶數" : "奇數") << endl;

    // 取兩數中的較大值
    int a = 15, b = 28;
    int maxVal = (a > b) ? a : b;
    cout << a << " 和 " << b << " 的較大值：" << maxVal << endl;

    // 絕對值
    int x = -7;
    int absX = (x >= 0) ? x : -x;
    cout << "|" << x << "| = " << absX << endl;

    return 0;
}
