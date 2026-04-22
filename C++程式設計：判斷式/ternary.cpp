#include <iostream>
#include <string>
using namespace std;

int main() {
    int score;
    cout << "請輸入分數：";
    cin >> score;

    // 三元運算子：簡化 if-else
    string result = (score >= 60) ? "及格" : "不及格";
    cout << result << endl;

    // 可以嵌套（但超過兩層就不建議了）
    string grade = (score >= 90) ? "A" :
                   (score >= 80) ? "B" :
                   (score >= 70) ? "C" :
                   (score >= 60) ? "D" : "F";
    cout << "等級：" << grade << endl;

    // 用於輸出（很常見的用法）
    int num;
    cout << "請輸入一個整數：";
    cin >> num;
    cout << num << " 是 " << (num % 2 == 0 ? "偶數" : "奇數") << endl;

    // 取兩數中的較大值
    int a = 15, b = 28;
    int maxVal = (a > b) ? a : b;
    cout << "較大值：" << maxVal << endl;

    return 0;
}